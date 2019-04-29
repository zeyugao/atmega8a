#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

#include <util/delay.h>
#include "../module/i2c_lcd1602.h"
#include "../module/custom_char.h"
int main() {
	I2C_LCD1602_Init();
	unsigned char c = 0;
	while (1) {
		I2C_LCD1602_WriteChar(0, 0, c + '0');
		c++;
		c %= 10;
		_delay_ms(1000);
	}
}