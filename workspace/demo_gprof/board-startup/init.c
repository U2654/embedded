/*See LICENSE of license details.*/

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "encoding.h"
#include "profil.h"
#include "intctl.h"




void timer_handler(uintptr_t epc)
{
	 	 clear_csr(mie, MIP_MTIP);



		 volatile uint64_t * mtime    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
		 volatile uint64_t * mtimecmp = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
		 uint64_t now = *mtime;

		 uint64_t then = now +(uint64_t)RTC_FREQ/1000;
		 *mtimecmp = then;

		 profile_handler(epc);


		 set_csr(mie, MIP_MTIP);
}

void trap_handler(uintptr_t mcause, uintptr_t epc)
{

	 if ((mcause & MCAUSE_INT) && ((mcause & MCAUSE_CAUSE) == IRQ_M_TIMER))
	      timer_handler(epc);


}
void _init()
{

}
