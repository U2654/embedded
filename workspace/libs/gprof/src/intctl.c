/* See LICENSE of license details.
 *
 * intctl.c
 *
 *  Created on: 03-May-2019
 *
 */
#include "encoding.h"
#include "intctl.h"
#include "proto.h"

void  NO_INSTRUMENT enable_timer_interrupts(void)
{

	clear_csr(mie, MIP_MTIP);

    volatile uint64_t * mtime    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t * mtimecmp = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
    uint64_t now = *mtime;
    uint64_t then = now + (uint64_t)RTC_FREQ/1000;
    *mtimecmp = then;

    /* Enable timer and all interrupts */
    set_csr(mie, MIP_MTIP);
    set_csr(mstatus, MSTATUS_MIE);

}

void  NO_INSTRUMENT disable_timer_interrupts( __attribute__ ((no_instrument_function)) ){
	clear_csr(mie, MIP_MTIP);
	clear_csr(mstatus, MSTATUS_MIE);
}
