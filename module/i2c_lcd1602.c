#include "i2c_lcd1602.h"

#include <util/delay.h>
#include "i2c_pcf8574t.h"

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYONOFF 0x08
#define LCD_CUR_DIS_SHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

#define ENTRY_DISPLAYNOSHIFT 0x00
#define ENTRY_DISPLAYSHIFT 0x01
#define ENTRY_DISPLAYDEC 0x00
#define ENTRY_DISPLAYINC 0x02

#define DISPLAY_BLINKOFF 0x00
#define DISPLAY_BLINKON 0x01
#define DISPLAY_CURSOROFF 0x00
#define DISPLAY_CURSORON 0x02
#define DISPLAY_OFF 0x00
#define DISPLAY_ON 0x04

#define LCD_CUR_SHIFT2LEFT 0x00
#define LCD_CUR_SHIFT2RIGHT 0x04

#define LCD_DIS_SHIFT2LEFT_CUR 0x08
#define LCD_DIS_SHIFT2RIGHT_CUR 0x0C

#define LCD_4BITMODE 0x00
#define LCD_8BITMODE 0x10
#define LCD_ONELINE 0x00
#define LCD_TWOLINE 0x08
#define LCD_5X8DOTS 0x00
#define LCD_5XADOTS 0x04

#define LCD_BACKLIGHTOFF 0x00
#define LCD_BACKLIGHTON 0x08
#define LCD_RS 0x01
#define LCD_RW 0x02
#define LCD_EN 0x04

#define I2C_SLAVE_ADDRESS 0x27
BYTE lcd_backlight = LCD_BACKLIGHTON;

BYTE WritePCF8574(BYTE data) {
	return I2C_WRITE_PCF8574((I2C_SLAVE_ADDRESS << 1), data | lcd_backlight);
}
void I2C_LCD1602_WR4bits(BYTE value) {
	WritePCF8574(value);
	_delay_us(1);
	WritePCF8574(value | LCD_EN);
	_delay_us(1);
	WritePCF8574(value & ~LCD_EN);
	_delay_us(50);
}
void I2C_LCD_WR8bits(BYTE value, BYTE mode) {
	BYTE high4bits = value & 0xF0;
	BYTE low4bits = (value << 4) & 0xF0;
	I2C_LCD1602_WR4bits((high4bits) | mode);
	I2C_LCD1602_WR4bits((low4bits) | mode);
}
void I2C_LCD1602_Init() {
	BYTE lcd_cmd = 0;
	_delay_ms(50);
	lcd_backlight = LCD_BACKLIGHTON;
	WritePCF8574(lcd_backlight);
	_delay_ms(100);

	I2C_LCD1602_WR4bits(0x03 << 4);
	_delay_us(4500);

	I2C_LCD1602_WR4bits(0x03 << 4);
	_delay_us(4500);

	I2C_LCD1602_WR4bits(0x03 << 4);
	_delay_us(150);
	I2C_LCD1602_WR4bits(0x02 << 4);

	I2C_LCD_WR8bits(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_TWOLINE | LCD_5X8DOTS, 0);
	lcd_cmd = DISPLAY_ON | DISPLAY_CURSORON | DISPLAY_BLINKOFF;
	I2C_LCD_WR8bits(LCD_DISPLAYONOFF | lcd_cmd, 0);

	I2C_LCD_WR8bits(LCD_CLEARDISPLAY, 0);
	_delay_us(2000);

	lcd_cmd = ENTRY_DISPLAYINC | ENTRY_DISPLAYNOSHIFT;
	I2C_LCD_WR8bits(LCD_ENTRYMODESET | lcd_cmd, 0);

	I2C_LCD_WR8bits(LCD_RETURNHOME, 0);
	_delay_us(2000);
}

void I2C_LCD1602_SetCursor(BYTE row, BYTE col) {
	int row_offsets[] = { 0x00, 0x40 };
	I2C_LCD_WR8bits(LCD_SETDDRAMADDR | (col + row_offsets[row]), 0);
}
void I2C_LCD1602_WriteNewChar(char value) {
	I2C_LCD_WR8bits(value, 1);
}

inline void I2C_LCD1602_WriteChar(BYTE row, BYTE col, char value) {
	I2C_LCD1602_SetCursor(row, col);
	I2C_LCD_WR8bits(value, 1);
}
void I2C_LCD1602_WriteString(BYTE row, BYTE col, const char* pString) {
	I2C_LCD1602_SetCursor(row, col);
	while ((*pString) != '\0') {
		I2C_LCD_WR8bits(*pString, 1);
		pString++;
	}
}

void I2C_LCD1602CreateChar(BYTE loc, BYTE charmap[]) {
	loc &= 0x7;
	I2C_LCD_WR8bits(LCD_SETCGRAMADDR | (loc << 3), 0);
	for (BYTE i = 0; i < 8; i++) {
		I2C_LCD_WR8bits(charmap[i], 1);
	}
}

void I2C_LCD1602_ClearLine(BYTE line) {
	I2C_LCD1602_SetCursor(line, 0);
	for (unsigned char i = 0; i < 40; i++) {
		I2C_LCD_WR8bits(' ', 1);
	}
	I2C_LCD1602_SetCursor(line, 0);
}

void I2C_LCD1602_ClearAll() {
	I2C_LCD1602_ClearLine(0);
	I2C_LCD1602_ClearLine(1);
}