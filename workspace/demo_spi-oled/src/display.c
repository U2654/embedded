// Original code from https://github.com/agra-uni-bremen/sifive-hifive1
#include "display.h"

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"

#define MAX_SPI_FREQ   ( 8000000)

static void sleep_u(uint64_t micros)
{
    volatile uint64_t * now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + ((micros * RTC_FREQ) / (1000 * 1000));
    while (*now < then){}
}

static uint32_t mapPinToReg(uint8_t pin)
{
    if(pin < 8)
    {
        return pin + PIN_0_OFFSET;
    }
    if(pin >= 8 && pin < 14)
    {
        return pin - 8;
    }
    //ignoring non-wired pin 14 <==> 8
    if(pin > 14 && pin < 20)
    {
        return pin - 6;
    }
    return 0;
}

void setPin(uint8_t pin, uint8_t val)
{
	if(val)
	{
		GPIO_REG(GPIO_OUTPUT_VAL) |= 1 << mapPinToReg(pin);
	}
	else
	{
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~(1 << mapPinToReg(pin));
	}
}

void spi_init(void)
{

	//Pins enable output
	GPIO_REG(GPIO_INPUT_EN)   &= ~(1 << mapPinToReg(OLED_SDIN) |
									1 << mapPinToReg(OLED_SCLK) |
									1 << mapPinToReg(OLED_CS));
	GPIO_REG(GPIO_OUTPUT_EN)  |= (1 << mapPinToReg(OLED_SDIN) |
									1 << mapPinToReg(OLED_SCLK) |
									1 << mapPinToReg(OLED_CS));

    // Select IOF SPI1.MOSI [SDIN] and SPI1.SCK [SLCK] and SPI1.SS0 [CS]
    GPIO_REG(GPIO_IOF_SEL)    &= ~((1 << mapPinToReg(OLED_SDIN)) |
    								(1 << mapPinToReg(OLED_SCLK)) |
									(1 << mapPinToReg(OLED_CS)));

    GPIO_REG(GPIO_IOF_EN )    |=  ((1 << mapPinToReg(OLED_SDIN)) |
    								(1 << mapPinToReg(OLED_SCLK)) |
    								(1 << mapPinToReg(OLED_CS)));

    // Set up SPI controller
    /** SPI clock divider: determines the speed of SPI
     * transfers.
     * The formula is CPU_FREQ/(1+SPI_SCKDIV)
     */
    SPI1_REG(SPI_REG_SCKDIV)    = (get_cpu_freq() / MAX_SPI_FREQ) - 1;
    SPI1_REG(SPI_REG_SCKMODE)   = 0; /* pol and pha both 0 - SCLK is active-high, */
    SPI1_REG(SPI_REG_CSID)      = OLED_CS_OFS;
    SPI1_REG(SPI_REG_CSDEF)     = 0xffff; /* CS is active-low */
    SPI1_REG(SPI_REG_CSMODE)    = SPI_CSMODE_HOLD; /* hold CS where possible */
    /* SPI1_REG(SPI_REG_DCSSCK)    = */
    /* SPI1_REG(SPI_REG_DSCKCS)    = */
    /* SPI1_REG(SPI_REG_DINTERCS)  = */
    /* SPI1_REG(SPI_REG_DINTERXFR) = */
    SPI1_REG(SPI_REG_FMT)       = SPI_FMT_PROTO(SPI_PROTO_S) | SPI_FMT_ENDIAN(SPI_ENDIAN_MSB) | SPI_FMT_DIR(SPI_DIR_TX) | SPI_FMT_LEN(8);
    /* SPI1_REG(SPI_REG_TXCTRL)    = 1; *//*interrupt when <1 in tx fifo (completion) */
    /* SPI1_REG(SPI_REG_RXCTRL)    = */
    /* SPI1_REG(SPI_REG_IE)        = SPI_IP_TXWM;	*/ /* enables TXWM-Interrupt */
}

void spi(uint8_t data)
{
    while (SPI1_REG(SPI_REG_TXFIFO) & SPI_TXFIFO_FULL)
    	asm volatile("nop");
    SPI1_REG(SPI_REG_TXFIFO) = data;
}


void mode_data(void)
{	//not already in data mode
	if(!(GPIO_REG(GPIO_OUTPUT_VAL) & (1 << mapPinToReg(OLED_DC))))
	{
		setPin(OLED_DC, 1);
	}
}

void mode_cmd(void)
{
	//not already in command mode
	if(GPIO_REG(GPIO_OUTPUT_VAL) & (1 << mapPinToReg(OLED_DC)))
	{
		setPin(OLED_DC, 0);
	}
}

void setDisplayOn(uint8_t on)
{
	mode_cmd();
	spi(0xAE | (on & 1));
}

void setChargePumpVoltage(uint8_t voltage)
{
	mode_cmd();
	spi(0b00110000 | (voltage & 0b11));
}

void invertColor(uint8_t invert)
{
	mode_cmd();
	spi(0b10100110 | (invert & 1));	//set 'normal' direction (1 = bright)
}

void setEntireDisplayOn(uint8_t allWhite)
{
	mode_cmd();
	spi(0b10100100 | (allWhite & 1));
}

void setDisplayStartLine(uint8_t startline)
{
	mode_cmd();
	spi(0b01000000 | (startline & 0b111111));
}

void setDisplayOffset(uint8_t something)
{
	mode_cmd();
    spi(0b11010011);	//double byte to set display offset to (y)0;
    spi(0b00000000);	//double byte to set display offset to (y)0;
}

void flipDisplay(uint8_t flip)
{
	mode_cmd();
	spi(0b11000000 | (0b1111 * (flip & 1)));
}

void setContrast(uint8_t contrast)
{
	/**
	 * Segment output current setting: ISEG = a/256* IREF * scale_factor
	 * Where a is contrast step, IREF is reference current (12.5uA), scale_factor = 16
	 */
	mode_cmd();
	spi(0b10000001);	//Contrast mode
	spi(contrast);
}

void fadeIn(uint64_t millis)
{
	for(uint8_t contrast = 0; contrast != 0xff; contrast++)
	{
		setContrast(contrast);
		sleep_u((millis * 1000) / 256);
	}
}

void fadeOut(uint64_t millis)
{
	for(uint8_t contrast = 0xff; contrast != 0; contrast--)
	{
		setContrast(contrast);
		sleep_u((millis * 1000) / 256);
	}
}

/** Initialize pmodoled module */
void oled_init()
{
    spi_init();

    // Initial setup

    //Enable RESET and D/C Pin
	GPIO_REG(GPIO_INPUT_EN)   &= ~(1 << mapPinToReg(OLED_RES) |
									1 << mapPinToReg(OLED_DC));
	GPIO_REG(GPIO_OUTPUT_EN)  |= (1 << mapPinToReg(OLED_RES) |
									1 << mapPinToReg(OLED_DC));
	setPin(OLED_DC, 0);

	//RESET
	setPin(OLED_RES,0);
	sleep_u(10);		//min 10us
	setPin(OLED_RES,1);
	sleep_u(100000);	//'about 100ms'

    // Command mode
	mode_cmd();

    // To see the bug better. Normally, this is the last thing to do.
    // setDisplayOn(1);

	// Initialize display to desired operating mode.

    setChargePumpVoltage(0b10);
    invertColor(0);
    //flipDisplay(1);
    setContrast(0xff);		//MY EYES!!!

    // 4. Clear screen (entire memory)
    oled_clear();
    setDisplayOn(1);
}

void set_x(unsigned col)
{
    mode_cmd();
    spi(0x00 | ((col+DISP_W_OFFS) & 0xf));
    spi(0x10 | (((col+DISP_W_OFFS) >> 4)&0xf));
    mode_data();
}
void set_row(unsigned row)
{
    mode_cmd();
    spi(0xb0 | (row & 0x7));
    mode_data();
}

void set_xrow(unsigned col, unsigned row)
{
    mode_cmd();
    spi(0x00 | ((col+DISP_W_OFFS) & 0xf));
    spi(0x10 | (((col+DISP_W_OFFS) >> 4)&0xf));
    spi(0xb0 | (row & 0x7));
    mode_data();
}

void oled_clear(void)
{
	for (unsigned y = 0; y < DISP_H/8; ++y) {
    	set_xrow(0, y);
		for (unsigned x=0; x < DISP_W; ++x) {
    		spi(0x00);
    	}
    }
	set_xrow(0,0);
}

