/*
  TwoWire.cpp - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
  
  04/2021 examplary implementation of few functions for fe310 by matt koenig.
*/

#include <string.h> // for memcpy
//#include "HardwareSerial.h"
#include "Wire.h"

#include "encoding.h"
#include "platform.h"

uint8_t TwoWire::rxBuffer[BUFFER_LENGTH];
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;
//uint8_t TwoWire::txAddress = 0;
uint8_t TwoWire::txBuffer[BUFFER_LENGTH+1];
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;
uint8_t TwoWire::transmitting = 0;
void (*TwoWire::user_onRequest)(void) = NULL;
void (*TwoWire::user_onReceive)(int) = NULL;


TwoWire::TwoWire()
{
}

void TwoWire::begin(void)
{
	// set up gpio pins to i2c use
	GPIO_REG(GPIO_IOF_SEL) &= ~((1 << IOF_I2C_SCL) | (1 << IOF_I2C_SDA));
	GPIO_REG(GPIO_IOF_EN)  |= ((1 << IOF_I2C_SCL) | (1 << IOF_I2C_SDA));
    setClock(100000);
}

// ignored frequency, set to 100khz
void TwoWire::setClock(uint32_t frequency)
{
	// prescaler to 100 kHz
	I2C_REG(I2C0_CONTROL) &= ~(1 << I2C_CTRL_EN);
	I2C_REG(I2C0_PRESCALE_HIGH) = 0x00;
	I2C_REG(I2C0_PRESCALE_LOW) = 0x1F; // = 100kHz
	I2C_REG(I2C0_CONTROL) |= (1 << I2C_CTRL_EN);
}

void TwoWire::begin(uint8_t address)
{
}

void TwoWire::beginTransmission(uint8_t address)
{
	I2C_REG(I2C0_TRANSMIT) = (address << 1);
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return;

//	txBuffer[0] = (address << 1);
//	transmitting = 1;
//	txBufferLength = 1;
}

size_t TwoWire::write(uint8_t data)
{
	// write reg add
	I2C_REG(I2C0_TRANSMIT) = data;
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_WR) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return 1;

}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
}

void TwoWire::flush(void)
{
}


uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
	return 0;
}


uint8_t TwoWire::requestFrom(uint8_t address, uint8_t length, uint8_t sendStop)
{
	// send read request
	I2C_REG(I2C0_TRANSMIT) = (address << 1) | 0x1;
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));

  for (uint8_t i = 0; i < length; ++i)
  {
    // read, ack and end
	if (i == length-1)
	{
	  I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_RD ) | ( 1 << I2C_CMD_ACK) | (1 << I2C_CMD_STO);		
	}
	else 
	{
		    I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_RD );
	}

    // wait
    while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));

    rxBuffer[i] = I2C_REG(I2C0_RECEIVE);
  }
  rxBufferIndex = 0;
  return length;
}

int TwoWire::available(void)
{
  return 0;
}

int TwoWire::read(void)
{
  return rxBuffer[rxBufferIndex++];
}

int TwoWire::peek(void)
{
  return -1;
}

// alternate function prototypes

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(int address)
{
	beginTransmission((uint8_t)address);
}

uint8_t TwoWire::endTransmission(void)
{
	return endTransmission(true);
}

void TwoWire::begin(int address)
{
	begin((uint8_t)address);
}

void TwoWire::onReceive( void (*function)(int) )
{
	user_onReceive = function;
}

void TwoWire::onRequest( void (*function)(void) )
{
	user_onRequest = function;
}

//TwoWire Wire = TwoWire();
TwoWire Wire;


