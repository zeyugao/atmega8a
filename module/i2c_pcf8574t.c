
#include "i2c_pcf8574t.h"

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

#define I2C_START 0x08
#define I2C_RESTART 0x10
#define I2C_MT_SLAW_ACK 0x18
#define I2C_MT_SLAW_NACK 0x20
#define I2C_MT_DATA_ACK 0x28
#define I2C_MT_DATA_NACK 0x30

#define I2C_MR_SLAR_ACK 0x40
#define I2C_MR_SLAR_NACK 0x48
#define I2C_MR_DATA_ACK 0x50
#define I2C_MR_DATA_NACK 0x58

#ifndef I2C_SLAVE_ADDRESS
#define I2C_SLAVE_ADDRESS 0x27
#endif

#define I2C_Start() (TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN))

#define I2C_Wait()                     \
	{                                  \
		while (!(TWCR & (1 << TWINT))) \
			;                          \
	}
#define I2C_GetStatus() (TWSR & 0xF8)
#define I2C_SendByte(uc)                   \
	{                                      \
		TWDR = (uc);                       \
		TWCR = (1 << TWINT) | (1 << TWEN); \
	}
#define I2C_StartXFER() (TWCR = (1 << TWINT) | (1 << TWEN))
#define I2C_SetACK() (TWCR |= (1 << TWEA))
#define I2C_SetNACK() (TWCR &= ~(1 << TWEA))
#define I2C_Stop() (TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN))

BYTE I2C_WRITE_PCF8574(BYTE sla_addr, BYTE bdata) {
	I2C_Start();
	I2C_Wait();
	if (I2C_GetStatus() != I2C_START)
		return 1;

	I2C_SendByte(sla_addr);
	I2C_Wait();
	if (I2C_GetStatus() != I2C_MT_SLAW_ACK) {
		I2C_Stop();
		return 1;
	}

	I2C_SendByte(bdata);
	I2C_Wait();
	if (I2C_GetStatus() != I2C_MT_DATA_ACK) {
		I2C_Stop();
		return 1;
	}
	I2C_Stop();
	return 0;
}