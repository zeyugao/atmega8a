#ifndef I2C_LCD1602_H
#define I2C_LCD1602_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

void I2C_LCD1602_Init();
void I2C_LCD1602_WriteNewChar(char value);
void I2C_LCD1602_SetCursor(BYTE row, BYTE col);
void I2C_LCD1602_WriteChar(BYTE row, BYTE col, char value);
void I2C_LCD1602_WriteString(BYTE row, BYTE col, const char* pString);
void I2C_LCD1602_CreateChar(BYTE loc,const BYTE charmap[]);
void I2C_LCD1602_ClearLine(BYTE line);
void I2C_LCD1602_ClearAll();

#endif // I2C_LCD1602_H