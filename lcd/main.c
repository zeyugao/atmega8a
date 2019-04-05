#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "atmega8a_i2c_lcd1602.h"

int main(void) {
	I2C_LCD1602_Init();

	I2C_LCD1602_WriteNewChar(0x7e);
	I2C_LCD1602_WriteChar(1, 0, 0xfb);
	I2C_LCD1602_WriteString(0, 2, "Welcome to USTC");
	I2C_LCD1602_WriteString(1, 2, "2018.7");

	while (1) {
		_delay_ms(1000);
		I2C_LCD_WR8bits(LCD_CUR_DIS_SHIFT | LCD_DIS_SHIFT2LEFT_CUR, 0);
	}
}