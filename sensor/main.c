#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include <stdlib.h>
#include "../module/usart.h"
#include "../module/dht11.h"
#include "../module/i2c_lcd1602.h"
#include "../module/adc.h"

#define DHT11 1
#define LIGHT 2

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

int main() {
	I2C_LCD1602_Init();
	usart_init(MYUBRR);
	unsigned char command = 3;
	unsigned char success = 0;
	unsigned char data[4];
	unsigned int distance;
	unsigned char len;

	char buffer[10];

	adc_init(0);
	while (1) {
		command = usart_receive();
		I2C_LCD1602_WriteChar(0, 10, command + '0');
		switch (command) {
			case DHT11:
				read_dht11(data);
				for (int i = 0; i < 4; i++) {
					I2C_LCD1602_WriteChar(0, 3 - i, data[i] + '0');
				}
				usart_send_array(data, 4);
				break;
			case LIGHT:
				read_adc(&data[0], &data[1]);
				itoa(data[0], buffer, 10);
				I2C_LCD1602_WriteString(0, 0, "    ");
				I2C_LCD1602_WriteString(0, 0, buffer);
				itoa(data[1], buffer, 10);
				I2C_LCD1602_WriteString(1, 0, "    ");
				I2C_LCD1602_WriteString(1, 0, buffer);
				usart_send_array(data, 2);
			default:
				break;
		}
	}
}