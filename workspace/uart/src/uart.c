#include "encoding.h"
#include "platform.h"
#include "wrap.h"

void delay(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 1000);
    while (*now < then);
}

// uart init
void uart_init()
{
	// set up gpio pins to uart use
	// see ch. 17.8
    GPIO_REG(GPIO_IOF_SEL)    &= ~IOF0_UART0_MASK;
    GPIO_REG(GPIO_IOF_EN)     |= IOF0_UART0_MASK;

    // enable uart
    // see ch. 18.6 and 18.7
    UART0_REG(UART_REG_TXCTRL) |= UART_TXEN;
    UART0_REG(UART_REG_RXCTRL) |= UART_RXEN;
}

void uart_putc(const char f_char)
{
	// wait
	// see ch. 18.4
	while (UART0_REG(UART_REG_TXFIFO) & (1 << 31));
	// if fifo empty, put char out
	UART0_REG(UART_REG_TXFIFO) = f_char;
}

const char* g_text = "Hello";

int main(int argc, char **argv)
{
	uart_init();

	while(1)
	{
		uint32_t i = 0;
		while (g_text[i])
		{
			uart_putc(g_text[i]);
			i++;
		}
		delay(1000);
	}
	return 0;
}
