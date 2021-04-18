#ifndef _SIFIVE_I2C_H
#define _SIFIVE_I2C_H


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

#define I2C0_0_BASE_ADDRESS 0x10016000
#define I2C0_0_SIZE 4096UL

#define I2C0

/* Register offsets */

#define I2C0_PRESCALE_LOW 0x00
#define I2C0_PRESCALE_HIGH 0x04
#define I2C0_CONTROL 0x08
#define I2C0_TRANSMIT 0x0c
#define I2C0_RECEIVE 0x0c
#define I2C0_COMMAND 0x10
#define I2C0_STATUS 0x10

#define I2C_REG(offset) _REG32(I2C0_0_BASE_ADDRESS, offset)

#endif /* _SIFIVE_I2C_H */
