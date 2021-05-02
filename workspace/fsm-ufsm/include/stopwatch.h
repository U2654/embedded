#ifndef UFSM_GEN_stopwatch_H__
#define UFSM_GEN_stopwatch_H__
#include <ufsm.h>
#ifndef NULL
 #define NULL (void *) 0
#endif
void resetTime(void);
void stopTime(void);
void startTime(void);
enum {
  reset,
  startstop,
};
struct ufsm_machine * get_StateMachine1(void);
#endif
