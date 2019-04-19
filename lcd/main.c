#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "../module/display.h"
#include "../module/keyboard.h"
#include "../module/atmega8a_i2c_lcd1602.h"
#include "../module/custom_char.h"
int main() {
	DDRB = 0xFF;
	PORTB = 0x3c;
	DDRC = 0x00;
	PORTC = 0x0F;
	DDRD = 0xFF;

	I2C_LCD1602_Init();

	BYTE char0[] = {
		OxOOO,
		OOxOO,
		OOOxO,
		OOxOO,
		OOOxO,
		OOOOx,
		OOOxO,
		OOxOO
	};
	BYTE char1[] = {
		OOOOO,
		OxOxO,
		xxxxx,
		xxxxx,
		OxxxO,
		OOxOO,
		OOOOO,
		OOOOO
	};
	I2C_LCD_1602CreateChar(0, char0);
	I2C_LCD_1602CreateChar(1, char1);
	I2C_LCD1602_WriteChar(0, 0, (char)0);
	I2C_LCD1602_WriteChar(0, 1, (char)1);
	while (1) {
		_delay_ms(1000);
	}
}