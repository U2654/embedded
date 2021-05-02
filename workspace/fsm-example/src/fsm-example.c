#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define EVENTBASED

#if defined(STATEPATTERN)
#define fsm fsmSP
#elif defined(TABLEBASED)
#define fsm fsmT
#elif defined(EVENTBASED)
#define fsm fsmE
#elif defined(STATEBASED)
#define fsm fsmS
#endif


time_t StartTime = 0.0;
double ElapsedSec = 0.0;

const int nbStates = 2;
const int nbEvents = 2;

typedef enum { STOPPED = 0, RUNNING = 1} state_t;
typedef enum { reset = 0, startstop = 1 } event_t;

state_t CurrentState = STOPPED;

/* action functions called by transition */
void startTime(void)
{
    StartTime = time(0);
    printf ("start\n");
}

void stopTime(void)
{
    ElapsedSec += difftime(time(0), StartTime);
    printf ("stop\n");
}

void resetTime(void)
{
    ElapsedSec = 0.0;
    printf ("reset\n");
}

/* state-based processing of fsm */
void fsmS(event_t event)
{
	switch(CurrentState) /* current state of type state_t */
	{
		case STOPPED:
			if (event == startstop) /* event of type event_t */
			{
				startTime();             /* action by transition */
				CurrentState = RUNNING;  /* new state */
			}
			else if (event == reset)
			{
				resetTime();
				CurrentState = STOPPED;
			}
			else { /* you shouldn't be here */}
			break;
		case RUNNING:
			if (event == startstop)
			{
				stopTime();
				CurrentState = STOPPED;
			}
			else if (event == reset)
			{
				resetTime();
				CurrentState = STOPPED;
			}
			else { /* you shouldn't be here */}
			break;
		default:
		/* you shouldn't be here */
		break;
	} 
}

/* event-based processing of fsm */
void fsmE(event_t event)
{
	switch (event)
	{
		case reset:							/* type is event_t */
			resetTime();					/* action of transition */
			if (CurrentState == RUNNING)	/* type is state_t */
			{
				CurrentState = STOPPED;
			}
			/* otherwise nothing to do */
		break;
		case startstop:
			if (CurrentState == RUNNING)
			{
				stopTime();
				CurrentState = STOPPED;
			}
			else if (CurrentState == STOPPED)
			{
				startTime();
				CurrentState = RUNNING;
			}
		break;
	}
}

/* table-based processing of fsm */
typedef void (*action_t)(void);
typedef struct {
	state_t nextState; action_t actionFunc; /* transistion data */
} table_cell_t;

/* all transitions of all states */
table_cell_t StateTable[nbStates][nbEvents] = {
    /* column for reset (0),  column fo startstop (1) */
	{ {STOPPED, resetTime},   {RUNNING, startTime} }, /* row for STOPPED (0) */
	{ {STOPPED, resetTime},   {STOPPED, stopTime} }   /* row for RUNNING (1) */
};

void fsmT(event_t event)
{
	StateTable[CurrentState][event].actionFunc();             /* call action */
	CurrentState = StateTable[CurrentState][event].nextState; /* transit     */
}


/* state pattern approach in C */
typedef struct CState_t* CState_p;

typedef struct CState_t				/* base class, me is this pointer */
{ 
  CState_p (*processEvent)(CState_p me, event_t e);	/* kind of virtual function */
} CState_t;

CState_t CStopped;		/* though instance, works as derived class */
CState_t CRunning;		/* though instance, works as derived class */

/* processEvent function of "class" Running */
CState_p running_processEvent(CState_p me, event_t e)
{
	if (e == startstop)
	{
		stopTime();
		return &CStopped;
	}
	else if (e == reset)
	{
		resetTime();
		return me;
	}
	return 0; /* should not happen */
}

/* processEvent function of "class" Stopped */
CState_p stopped_processEvent(CState_p me, event_t e)
{
	if (e == startstop)
	{
		startTime();
		return &CRunning;
	}
	else if (e == reset)
	{
		resetTime();
		return me;
	}
	return 0; /* should not happen */
}

/* Holds pointer to base "class" */
CState_p CurrentCState;

void fsmSP(event_t event)
{
	/* calls "virtual" functions */
	CurrentCState = CurrentCState->processEvent(CurrentCState, event);
}

/* simulate some events */
int main(int argc, char **argv)
{
	/* init state pattern instead c'tors */
	/* set the "virtual" functions */
	CRunning.processEvent = &running_processEvent;
	CStopped.processEvent = &stopped_processEvent;
	/* set initial state */
	CurrentCState = &CStopped;	

	/* init */
	resetTime();
	CurrentState = STOPPED;

	printf("Start at 0 and end at 1:\n");
    printf("Elapsed: %f\n", ElapsedSec);
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);
    sleep(1);
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);
	printf("\n");

	printf("Start at 1 and reset:\n");
	fsm(startstop);
    sleep(1);
    printf("Elapsed: %f\n", ElapsedSec);
	fsm(reset);
    printf("Elapsed: %f\n", ElapsedSec);
	printf("\n");

	printf("Start at 0, stop at 1, continue, stop at 2\n");
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);
    sleep(1);
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);
    sleep(1);
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);
    sleep(1);
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);
	printf("\n");

	printf("Start at 2, reset, start at 0, stop at 1\n");
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);
    sleep(1);
	fsm(reset);
    printf("Elapsed: %f\n", ElapsedSec);
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);
    sleep(1);
	fsm(startstop);
    printf("Elapsed: %f\n", ElapsedSec);

    return 0;
}



