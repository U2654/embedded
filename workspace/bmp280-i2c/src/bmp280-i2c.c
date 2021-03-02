// See LICENSE for license details.
#include "encoding.h"
#include "platform.h"
#include "wrap.h"
#include <stdio.h>

#define IOF_I2C_SDA 12
#define IOF_I2C_SCL 13

#define I2C_CMD_STA 7
#define I2C_CMD_STO 6
#define I2C_CMD_RD 5
#define I2C_CMD_WR 4
#define I2C_CMD_ACK 3
#define I2C_CMD_IACK 0

#define I2C_STAT_RXACK 7
#define I2C_STAT_BUSY 6
#define I2C_STAT_ARLO 5
#define I2C_STAT_TIP 1
#define I2C_STAT_IF 0

#define I2C_CTRL_EN 7
#define I2C_CTRL_IE 6

/* From i2c@10016000 */
#define METAL_SIFIVE_I2C0_10016000_BASE_ADDRESS 268525568UL
#define METAL_SIFIVE_I2C0_0_BASE_ADDRESS 268525568UL
#define METAL_SIFIVE_I2C0_10016000_SIZE 4096UL
#define METAL_SIFIVE_I2C0_0_SIZE 4096UL

#define METAL_SIFIVE_I2C0
#define METAL_SIFIVE_I2C0_PRESCALE_LOW 0UL
#define METAL_SIFIVE_I2C0_PRESCALE_HIGH 4UL
#define METAL_SIFIVE_I2C0_CONTROL 8UL
#define METAL_SIFIVE_I2C0_TRANSMIT 12UL
#define METAL_SIFIVE_I2C0_RECEIVE 12UL
#define METAL_SIFIVE_I2C0_COMMAND 16UL
#define METAL_SIFIVE_I2C0_STATUS 16UL

#define I2C_REG(offset) _REG32(METAL_SIFIVE_I2C0_0_BASE_ADDRESS, offset)

#define I2C_SL_ADDR 0x76

void delay(uint32_t f_milliseconds)
{
    volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + f_milliseconds*(RTC_FREQ / 2000);
    while (*now < then);
}

// i2c init
void i2c_init()
{
	// set up gpio pins to i2c use
	GPIO_REG(GPIO_IOF_SEL) &= ~((1 << IOF_I2C_SCL) | (1 << IOF_I2C_SDA));
	GPIO_REG(GPIO_IOF_EN)  |= ((1 << IOF_I2C_SCL) | (1 << IOF_I2C_SDA));

	// prescaler to 100 kHz
	I2C_REG(METAL_SIFIVE_I2C0_CONTROL) &= ~(1 << I2C_CTRL_EN);
	I2C_REG(METAL_SIFIVE_I2C0_PRESCALE_HIGH) = 0x00;
	I2C_REG(METAL_SIFIVE_I2C0_PRESCALE_LOW) = 0x1F; // = 100kHz
	I2C_REG(METAL_SIFIVE_I2C0_CONTROL) |= (1 << I2C_CTRL_EN);
}

void i2c_writeReg(const uint8_t f_addr, const uint8_t f_data)
{
	// write address
	I2C_REG(METAL_SIFIVE_I2C0_TRANSMIT) = (I2C_SL_ADDR << 1);
	I2C_REG(METAL_SIFIVE_I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return;

	// write reg add
	I2C_REG(METAL_SIFIVE_I2C0_TRANSMIT) = f_addr;
	I2C_REG(METAL_SIFIVE_I2C0_COMMAND) = (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return;

	// write data
	I2C_REG(METAL_SIFIVE_I2C0_TRANSMIT) = f_data;
	I2C_REG(METAL_SIFIVE_I2C0_COMMAND) = (1 << I2C_CMD_WR) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return;

}

uint8_t i2c_read(const uint8_t f_addr)
{
	// write address
	I2C_REG(METAL_SIFIVE_I2C0_TRANSMIT) = (I2C_SL_ADDR << 1);
	I2C_REG(METAL_SIFIVE_I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return 0;

	// write addr
	I2C_REG(METAL_SIFIVE_I2C0_TRANSMIT) = f_addr;
	I2C_REG(METAL_SIFIVE_I2C0_COMMAND) = (1 << I2C_CMD_WR) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return 0;

	// send read request
	I2C_REG(METAL_SIFIVE_I2C0_TRANSMIT) = (I2C_SL_ADDR << 1) | 0x1;
	I2C_REG(METAL_SIFIVE_I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_TIP));

	// read, ack and end
	I2C_REG(METAL_SIFIVE_I2C0_COMMAND) = (1 << I2C_CMD_RD ) | ( 1 << I2C_CMD_ACK) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(METAL_SIFIVE_I2C0_STATUS) & (1 << I2C_STAT_TIP));

	uint8_t rx = 0;
	rx = I2C_REG(METAL_SIFIVE_I2C0_RECEIVE);

	return (uint8_t)(rx & 0xff);
}


int main(int argc, char **argv)
{
	// init baud
	i2c_init();

	// show chip id
	uint8_t chip_id = i2c_read(0xd0);
	printf("chip id:%u \n", chip_id);

	// config: iir off, standby 500ms, i2c 
	// meas: osrs_p: skip, osrs_t: 1, normal mode 

	i2c_writeReg(0xf5, 0x84); //config
	i2c_writeReg(0xf4, 0x23); //ctrl_meas

	while(1)
	{
		// read temperature
	 	uint8_t msb = i2c_read(0xfa);
		printf("%u \n", msb);
		uint8_t lsb = i2c_read(0xfb);
		printf("%u \n", lsb);

		// conversion missing... 
  
		delay(1000);
	}
	return 0;
}
