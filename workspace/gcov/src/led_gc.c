#include "platform.h"
#include "wrap.h"
#include "startup.h"
#include "gcov.h"

//typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *)(P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38

#define BLUE_LED 5

int main(void)
{
	_init();
	// setup LED as output
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << BLUE_LED;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);

	volatile uint32_t i = 0, j = 0;
	while (j++ < 10)
	{
		// toggle only blue LED
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << BLUE_LED);
		// wait..
		waitcount();

		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);
		waitcount();
	}
}


