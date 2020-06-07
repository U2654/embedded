// See LICENSE for license details.

#include "encoding.h"
#include "platform.h"

void delay(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 2000);
    while (*now < then);
}

// spi init
void spi_init()
{
	// set up gpio pins to spi use
	GPIO_REG(GPIO_IOF_SEL) &= ~(1 << IOF_SPI1_SCK) | (1 << IOF_SPI1_MOSI) | (1 << IOF_SPI1_MISO) | (1 << IOF_SPI1_SS0);
	GPIO_REG(GPIO_IOF_EN)  |= (1 << IOF_SPI1_SCK) | (1 << IOF_SPI1_MOSI) | (1 << IOF_SPI1_MISO) | (1 << IOF_SPI1_SS0);


	// attention: assumption is everything is reset default. cs is controlled manually.
	// set up spi ckmode to 0b11
	SPI1_REG(SPI_REG_SCKMODE) = 3;

	// frame format, see ch. 18.7
	SPI1_REG(SPI_REG_FMT) =
			 SPI_FMT_PROTO(SPI_PROTO_S) |
			 SPI_FMT_ENDIAN(SPI_ENDIAN_MSB) |
	    	 SPI_FMT_DIR(SPI_DIR_RX) |
			 SPI_FMT_LEN(8);
	// clock divisor, see ch. 18.4, 100kH for arty
	SPI1_REG(SPI_REG_SCKDIV)  = 324;
}

uint8_t spi_transfer(const uint8_t f_char)
{
	// wait
	while (SPI1_REG(SPI_REG_TXFIFO) & SPI_TXFIFO_FULL);

	// empty -> transmit
	SPI1_REG(SPI_REG_TXFIFO) = (uint32_t) f_char;

	volatile uint32_t rx;
	// wait, empty -> received
	while ((rx = SPI1_REG(SPI_REG_RXFIFO)) & SPI_RXFIFO_EMPTY);

	return (uint8_t)(rx & 0xff);
}

int main(int argc, char **argv)
{
	spi_init();

	// cs mode hold for transfer
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
		delay(1000);
	}
	return 0;
}
