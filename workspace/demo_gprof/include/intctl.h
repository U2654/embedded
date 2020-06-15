#ifndef _INTCTL_H
#define _INTCTL_H

#include "proto.h"

#include <stdint.h>


#define MCAUSE_INT         0x80000000
#define MCAUSE_CAUSE       0x7FFFFFFF


#define CLINT_MSIP 0x0000
#define CLINT_MSIP_size   0x4
#define CLINT_MTIMECMP 0x4000
#define CLINT_MTIMECMP_size 0x8
#define CLINT_MTIME 0xBFF8
#define CLINT_MTIME_size 0x8


#define CLINT_CTRL_ADDR 0x02000000


#define RTC_FREQ 32768


void  NO_INSTRUMENT enable_timer_interrupts(void);
void  NO_INSTRUMENT disable_timer_interrupts(void);



#endif
