#include "encoding.h"
#include "platform.h"
#include "wrap.h"
#include "startup.h"
#include <stdio.h>

#define I2C_SL_ADDR 0x1d

void delay(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 1000);
    while (*now < then);
}

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

// i2c init
void i2c_init()
{
	// set up gpio pins to i2c use
	GPIO_REG(GPIO_IOF_SEL) &= ~((1 << IOF_I2C_SCL) | (1 << IOF_I2C_SDA));
	GPIO_REG(GPIO_IOF_EN)  |= ((1 << IOF_I2C_SCL) | (1 << IOF_I2C_SDA));

	// prescaler to 100 kHz
	I2C_REG(I2C0_CONTROL) &= ~(1 << I2C_CTRL_EN);
	I2C_REG(I2C0_PRESCALE_HIGH) = 0x00;
	I2C_REG(I2C0_PRESCALE_LOW) = 0x1F; // = 100kHz
	I2C_REG(I2C0_CONTROL) |= (1 << I2C_CTRL_EN);

}

void i2c_writeReg(const uint8_t f_addr, const uint8_t f_data)
{
	// write address
	I2C_REG(I2C0_TRANSMIT) = (I2C_SL_ADDR << 1);
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return;

	// write reg add
	I2C_REG(I2C0_TRANSMIT) = f_addr;
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return;

	// write data
	I2C_REG(I2C0_TRANSMIT) = f_data;
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_WR) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return;

}

uint8_t i2c_readReg(const uint8_t f_addr)
{
	// write address
	I2C_REG(I2C0_TRANSMIT) = (I2C_SL_ADDR << 1);
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return 0;

	// write reg addr
	I2C_REG(I2C0_TRANSMIT) = f_addr;
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_WR) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return 0;

	// send read request
	I2C_REG(I2C0_TRANSMIT) = (I2C_SL_ADDR << 1) | 0x1;
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));

	// read, ack and end
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_RD ) | ( 1 << I2C_CMD_ACK) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));

	uint8_t rx = 0;
	rx = I2C_REG(I2C0_RECEIVE);

	return (uint8_t)(rx & 0xff);
}

int main(int argc, char **argv)
{
	uart_init();
	i2c_init();

	i2c_writeReg(0x31, 0x01); // range 4g
	i2c_writeReg(0x2d, 0x08); // measure

	uint8_t r[6];
	while(1)
	{
		uint8_t regAdd = 0x32;
		for (size_t i = 0; i < 6; ++i)
		{
			r[i] = i2c_readReg(regAdd++);
		}
 	    volatile int16_t x = ((int16_t)r[1]<<8)|(int16_t)r[0];
	    volatile int16_t y = ((int16_t)r[3]<<8)|(int16_t)r[2];
	    volatile int16_t z = ((int16_t)r[5]<<8)|(int16_t)r[4];
		// process here x, y, z
		printf("%d %d %d\n", x, y, z);
		delay(250);
	}
	return 0;
}
