#include "wrap.h"
#include "startup.h"
#include <stdlib.h>

typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))

const uint32_t GPIO_BASE = 0x10012000;
const uint32_t GPIO_INPUT_EN = 0x4;
const uint32_t GPIO_OUTPUT_EN = 0x8;
const uint32_t GPIO_OUTPUT_VAL = 0xc;
const uint32_t GPIO_IOF_EN = 0x38;

const uint32_t BLUE_LED = 5;


int main (void)
{
	volatile int i; 
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1u << BLUE_LED); 
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1u << BLUE_LED); 
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= (1u << BLUE_LED); 
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1u << BLUE_LED); 

	while (1)
	{
		asm volatile("nop");
	}

	return 0;
}
