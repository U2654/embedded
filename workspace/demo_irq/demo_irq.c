// Press button for led

typedef unsigned int uint32_t;

#define REG(P) (*(volatile uint32_t *) (P))

#define GPIO_BASE 		0x10012000
#define GPIO_INPUT_VAL 	0x0
#define GPIO_INPUT_EN 	0x4
#define GPIO_OUTPUT_EN 	0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_FALL_IE 	0x20
#define GPIO_RISE_IE 	0x18
#define GPIO_RISE_IP 	0x1c
#define GPIO_PULLUP_EN 	0x10

#define PLIC_BASE   0x0C000000
#define PLIC_ENABLE 0x2000
#define PLIC_THRESH 0x200000
#define PLIC_CLAIM  0x200004

#define RED_LED 22
#define GREEN_LED 19
#define BLUE_LED 21
#define BUTTON 23

void irq_handler() __attribute((interrupt));

void init_gpio()
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
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << BUTTON);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << BUTTON);
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << BUTTON;
	REG(GPIO_BASE + GPIO_PULLUP_EN) |= 1 << BUTTON;
}

void irq_handler()
{
	// claim interrupt
	uint32_t nb = REG(PLIC_BASE + PLIC_CLAIM);

	// toggle led
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) ^= (1 << RED_LED);

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BUTTON);

	// complete interrupt
	REG(PLIC_BASE + PLIC_CLAIM) = nb;
}


void init_irq()
{
    // PLIC, 51 sources, 7 priorities
    // all off
    REG(PLIC_BASE + PLIC_ENABLE) = 0;
    REG(PLIC_BASE + PLIC_ENABLE + 4) = 0;
    // threshold 0
    REG(PLIC_BASE + PLIC_THRESH) = 0;

    // enable irq for button and set priority for button to 1
    // interrupts for gpio start at 8
    REG(PLIC_BASE + PLIC_ENABLE) |= (1 << (8+BUTTON));
    REG(PLIC_BASE + 4*(8+BUTTON)) = 1;

    // set handler
    asm volatile ("csrw mtvec, %0" :: "r"(irq_handler));

	// irq at rising
    REG(GPIO_BASE + GPIO_RISE_IE) |= (1 << BUTTON);

	// clear gpio pending interrupt
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BUTTON);

    // enable plic interrupts, set meie
    asm volatile ("csrw mie, %0" :: "r"(1<<11));


    // Enable all interrupts, set mie
    asm volatile ("csrw mstatus, %0" :: "i"(0x8));
}


int main (void)
{
	init_gpio();
	init_irq();

	volatile uint32_t i = 0;

	// wait for interrupt..
	while(1)
	{
//		for (i = 0; i < 0x800000; ++i);
		asm volatile("wfi");
	}
}
