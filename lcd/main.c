#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

#include <util/delay.h>
#include "../module/i2c_lcd1602.h"
#include "../module/custom_char.h"
int main() {
	DDRB = 0xFF;
	PORTB = 0x3c;
	DDRC = 0x00;
	PORTC = 0x0F;
	DDRD = 0xFF;

	unsigned char map[8][5] = {
		{ 0, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 1 },
		{ 0, 1, 1, 0, 1 },
		{ 0, 1, 1, 0, 1 },
		{ 0, 1, 0, 0, 1 },
		{ 0, 1, 1, 0, 1 },
		{ 0, 1, 0, 0, 1 },
		{ 0, 1, 1, 0, 1 },
	};
	I2C_LCD1602_Init();
	unsigned char char0[8];
	for (int i = 0; i < 8; i++) {
		char0[i] = pixel_map_to_data(map[i]);
	}

	I2C_LCD1602_CreateChar(0, char0);
	I2C_LCD1602_WriteChar(0, 0, (char)0);
	while (1) {
		_delay_ms(1000);
	}
}