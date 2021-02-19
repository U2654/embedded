// Hello World Blinky

typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc

#define RED_LED 22
#define GREEN_LED 19
#define BLUE_LED 21

int main (void)
{
	// setup LEDs as output
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << RED_LED);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << RED_LED;
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << RED_LED);

//	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << GREEN_LED);
//	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << GREEN_LED;
//	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << GREEN_LED);
//
//	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << BLUE_LED);
//	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << BLUE_LED;
//	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << BLUE_LED);
//
	volatile uint32_t i = 0;
	while(1)
	{
		// toggle only red LED
		REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << RED_LED);
		// wait..
		for (i = 0; i < 84210; i++){}

		REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << RED_LED);
		for (i = 0; i < 84210; i++){}
	}
}
