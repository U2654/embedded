#include "encoding.h"
#include "platform.h"
#include <stdio.h>

void delay(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 1000);
    while (*now < then);
}

// spi init
void spi_init()
{
	// set up gpio pins to spi use, see ch. 17.8
	GPIO_REG(GPIO_IOF_SEL) &= ~((1 << IOF_SPI1_SCK) | (1 << IOF_SPI1_MOSI) | (1 << IOF_SPI1_MISO) | (1 << IOF_SPI1_SS0));
	GPIO_REG(GPIO_IOF_EN)  |= (1 << IOF_SPI1_SCK) | (1 << IOF_SPI1_MOSI) | (1 << IOF_SPI1_MISO) | (1 << IOF_SPI1_SS0);
	// attention: assumption is everything is reset default. cs is controlled manually.
	// set up spi ckmode to 0b11
	SPI1_REG(SPI_REG_SCKMODE) = 3;
	// frame format, see ch. 19.7
	SPI1_REG(SPI_REG_FMT) =
			 SPI_FMT_PROTO(SPI_PROTO_S) |
			 SPI_FMT_ENDIAN(SPI_ENDIAN_MSB) |
	    	 SPI_FMT_DIR(SPI_DIR_RX) |
			 SPI_FMT_LEN(8);
	// set cs id, see ch. 19.6
	SPI1_REG(SPI_REG_CSID) = 0;
	// clock divisor, see ch. 19.4 (assumption 16MHz clock -> 64KHz spi)
	SPI1_REG(SPI_REG_SCKDIV)  = 124;
}

uint8_t spi_transfer(const uint8_t f_char)
{
	// see ch. 19.11
	// wait
	while (SPI1_REG(SPI_REG_TXFIFO) & SPI_TXFIFO_FULL);
	// empty -> transmit
	SPI1_REG(SPI_REG_TXFIFO) = (uint32_t) f_char;

	// see ch. 19.12
	volatile uint32_t rx;
	// wait, empty -> received
	while ((rx = SPI1_REG(SPI_REG_RXFIFO)) & SPI_RXFIFO_EMPTY);

	return (uint8_t)(rx & 0xff);
}

int main(int argc, char **argv)
{
	spi_init();

	// cs mode hold for transfer, see ch. 19.8
    SPI1_REG(SPI_REG_CSMODE) = SPI_CSMODE_HOLD;
	spi_transfer(0x31);
	spi_transfer(0x01);
	spi_transfer(0x2d);
	spi_transfer(0x08);

	uint8_t r[6];
	while(1)
	{
	    SPI1_REG(SPI_REG_CSMODE) = SPI_CSMODE_HOLD;
		spi_transfer(0x32 | 0x80 | 0x40);
		for (uint8_t i = 0; i < 6; ++i)
		{
			r[i] = spi_transfer(0x0);
		}
		// transfer done, cs mode off
	    SPI1_REG(SPI_REG_CSMODE) = SPI_CSMODE_OFF;
 	    volatile int16_t x = ((int16_t)r[1]<<8)|(int16_t)r[0];
	    volatile int16_t y = ((int16_t)r[3]<<8)|(int16_t)r[2];
	    volatile int16_t z = ((int16_t)r[5]<<8)|(int16_t)r[4];
		// process here x, y, z
		delay(1000);
	}
	return 0;
}
