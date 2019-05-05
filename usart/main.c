
#define F_CPU 8000000UL

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
	while (1) {
		usart_send('0'+sizeof(unsigned long));
		_delay_ms(1000);
	}
	return 0;
}
