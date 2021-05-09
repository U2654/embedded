#include "encoding.h"
#include "platform.h"
#include "wrap.h"
#include "startup.h"

void delay(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 1000);
    while (*now < then);
}

void uart_putc(const char f_char)
{
	// wait
	// see ch. 18.4
	while (UART0_REG(UART_REG_TXFIFO) & (1 << 31));
	// if fifo empty, put char out
	UART0_REG(UART_REG_TXFIFO) = f_char;
}

void aon_sleep()
{
	// default values, ch. 15.4
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUWAKEUPI0) = 0x3f0;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUWAKEUPI1) = 0x2f8;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUWAKEUPI2) = 0x030;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUWAKEUPI3) = 0x030;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUWAKEUPI4) = 0x030;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUWAKEUPI5) = 0x030;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUWAKEUPI6) = 0x030;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUWAKEUPI7) = 0x030;

	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUSLEEPI0) = 0x2f0;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUSLEEPI1) = 0x3f0;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUSLEEPI2) = 0x3d0;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUSLEEPI3) = 0x3c0;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUSLEEPI4) = 0x3c0;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUSLEEPI5) = 0x3c0;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUSLEEPI6) = 0x3c0;
	// AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// AON_REG(AON_PMUSLEEPI7) = 0x3c0;

	// ch 15.7 wake on timer, wakeup and reset button signal
	AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	AON_REG(AON_PMUIE) |= 0x3;

	// ch. 16.2 one increment = 1s
	// rtc should continue running
	AON_REG(AON_RTCCFG) |=  0x0000100f;
	// wake up in 30 seconds
	uint32_t now = AON_REG(AON_RTCS);
	uint32_t then = now + 30;
	AON_REG(AON_RTCCMP) = then;

	// send to sleep
	// unlook, ch. 14.3
	AON_REG(AON_PMUKEY) = AON_WDOGKEY_VALUE;
	// sleep, ch 14.5
	AON_REG(AON_PMUSLEEP) = 1;
}

void sendString( const char * pcString )
{
	const uint32_t ulTxFifoFullBit = 0x80000000UL;

	while( *pcString != 0x00 )
	{
		while( ( UART0_REG( UART_REG_TXFIFO ) & ulTxFifoFullBit ) != 0UL );
		UART0_REG( UART_REG_TXFIFO ) = *pcString;
		pcString++;
	}
}

int main(int argc, char **argv)
{
	_init();

    uint32_t x = AON_REG(AON_PMUCAUSE);
    if (x & 0x1)
    {
        sendString("Awake by timer\n");
    }
    else if (x & 0x2)
    {
        sendString("Awake by button\n");
    }
    else
    {
        sendString("Awake by reset\n");
    }

	delay(2000);
	sendString("Go sleeping\n");

    aon_sleep();
	return 0;
}
