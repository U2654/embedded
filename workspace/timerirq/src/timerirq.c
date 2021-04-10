#include <stdint.h>
#include "encoding.h"

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38

#define CLINT_CTRL_ADDR 0x02000000
#define CLINT_MTIME 0xbff8
#define CLINT_MTIMECMP 0x4000

#define RTC_FREQ 32768

#define BLUE_LED 5

void irq_handler() __attribute((interrupt));

void set_timer1s()
{
	volatile uint64_t * mtime   = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
	volatile uint64_t * mtimecmp = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
	uint64_t now = *mtime;
	uint64_t then = now + 1 * RTC_FREQ;
	*mtimecmp = then;
}

void irq_handler()
{
	// what's happening?
	unsigned long mcause_value = read_csr(mcause);

	// take only interrupts
	if (mcause_value & 0x80000000)
	{
		// and only timer interrupts
		if ((mcause_value & 0x7fffffff) == 7)
		{
			// restart 
			set_timer1s();
			// togle led
			REG(GPIO_BASE + GPIO_OUTPUT_VAL) ^= (1 << BLUE_LED);
		}
		//else if ()
	}
}

int main (void)
{
	// setup LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << BLUE_LED;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);

	// disable all interrupts
    clear_csr(mstatus, MSTATUS_MIE);

    // Timer-interrupt with 1 s
    set_timer1s();

    // enable
    set_csr(mie, MIP_MTIP);

    // Set handler
    write_csr(mtvec, &irq_handler);

    // Enable interrupts in general
    set_csr(mstatus, MSTATUS_MIE);

	volatile uint32_t i = 0;
	while(1)
	{
		asm volatile("wfi");
	}
}
