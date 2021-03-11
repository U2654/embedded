#include "encoding.h"
#include "platform.h"
#include "wrap.h"
#include <stdio.h>


#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc

#define RED_LED 22 
//22
#define GREEN_LED 19
#define BLUE_LED 21

int main (void)
{
	// setup LEDs as output
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << RED_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << RED_LED;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << RED_LED);

	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << GREEN_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << GREEN_LED;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << GREEN_LED);

	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << BLUE_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << BLUE_LED;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);

	volatile uint32_t i = 0;
	while(1)
	{
		printf("LED on\n");
		// toggle only red LED
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << RED_LED);
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << GREEN_LED);
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << BLUE_LED);
		// wait..
		for (i = 0; i < 184210; i++){}

		printf("LED off\n");
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << RED_LED);
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << GREEN_LED);
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);
		for (i = 0; i < 184210; i++){}
	}
}
