#include <ufsm.h>
#include <stdio.h>
#include "stopwatch.h"
#include "platform.h"
#include "encoding.h"
#include "wrap.h"

uint64_t StartMeasure = 0;
uint64_t ElapsedSec = 0;

void delay(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + (f_milliseconds*RTC_FREQ)/1000;
    while (*now < then);
}


void startTime(void)
{
    StartMeasure = get_timer_value();
    printf ("start\n");
}

void stopTime(void)
{
    uint64_t now = get_timer_value();
    uint64_t diff = now - StartMeasure;
    diff = 1000*diff / RTC_FREQ;
    ElapsedSec += diff;
    printf ("stop\n");
}

void resetTime(void)
{
    ElapsedSec = 0;
    printf ("reset\n");
}

int main(int argc, char **argv)
{
    struct ufsm_machine *m = get_StateMachine1();

    ufsm_init_machine(m);
    while (1) 
    {
        ufsm_process(m, startstop);
        delay(1000);
        ufsm_process(m, startstop);
        uint32_t mout = (uint32_t) ElapsedSec;
        printf("Elapsed: %d\n", mout);
    }

    return 0;
}

