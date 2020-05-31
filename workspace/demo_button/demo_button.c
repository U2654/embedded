// Press button for led

typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 0x10012000
#define GPIO_INPUT_VAL 0x0
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc

#define RED_LED 22
#define GREEN_LED 19
#define BLUE_LED 21
#define BUTTON 23

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

	// setup button as input
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << BUTTON;
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << BUTTON);


	volatile uint32_t i = 0;

	// polling
	while(1)
	{
		// a little delay
		for (i = 0; i < 184210; i++){}

		// check if button pressed and if turn led on else off
		// attention: no debouncing.
		if (REG(GPIO_BASE + GPIO_INPUT_VAL) & (1 << BUTTON))
		{
			REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << RED_LED);
		}
		else
		{
			REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << RED_LED);
		}
	}
}
