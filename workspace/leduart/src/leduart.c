#include "encoding.h"
#include "platform.h"
#include "wrap.h"
#include "startup.h"
#include <stdio.h>

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000

#define BLUE_LED 5

int main (void)
{
	// setup LEDs as output
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << BLUE_LED;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);

	volatile uint32_t i = 0;
	while(1)
	{
		printf("LED off 12345\n");
		// toggle only blue LED
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << BLUE_LED);
		// wait..
		for (i = 0; i < 184210; i++){}

		printf("LED on\n");
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);
		for (i = 0; i < 184210; i++){}
	}
}
