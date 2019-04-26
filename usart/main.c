
#define F_CPU 1000000UL

#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif
#include <avr/interrupt.h>

#include "../module/i2c_lcd1602.h"
#include "../module/usart.h"

char buffer[10];

int main() {
	usart_init(MYUBRR);
	I2C_LCD1602_Init();
	I2C_LCD1602_WriteString(1, 1, "Hello");
	while (1) {
		unsigned char c = usart_receive();
		usart_send(c);
		I2C_LCD1602_WriteChar(0, 0, c);
		//itoa(c, buffer, 10);
		//I2C_LCD1602_WriteString(0, 0, "    ");
		//I2C_LCD1602_WriteString(0, 0, buffer);
		//unsigned char c = usart_receive();
		//I2C_LCD1602_WriteString(0, 0, "Hello world");
		//for (unsigned char i = 0; i < 255; i++) {
		//	usart_send(i);
		//	char buffer[10];
		//	itoa(i, buffer, 10);
		//	I2C_LCD1602_WriteString(0, 0, buffer);
		//}
		//while (1)
		//	;
	}
	return 0;
}
