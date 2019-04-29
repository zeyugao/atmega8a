#ifndef F_CPU
#define F_CPU 8000000L
#endif

#include <avr/io.h>
#include "../module/atmega8a_i2c_lcd1602.h"
#include "../module/dht11.h"
#include "../module/display.h"

int main() {
	BYTE toggle = 0;
	init_display();
	I2C_LCD1602_Init();
	BYTE *dht11_lcd1602_data;
	while (1) {
		DHT11_run();
		dht11_lcd1602_data = get_dht11_data();
		I2C_LCD1602_WriteString(0, 0, "Temperature :");
		I2C_LCD1602_WriteNewChar(dht11_lcd1602_data[3] + '0');
		I2C_LCD1602_WriteNewChar(dht11_lcd1602_data[2] + '0');

		I2C_LCD1602_WriteString(1, 0, "Humidity :");
		I2C_LCD1602_WriteNewChar(dht11_lcd1602_data[1] + '0');
		I2C_LCD1602_WriteNewChar(dht11_lcd1602_data[0] + '0');

		display(dht11_lcd1602_data[3] * 1000 +
				  dht11_lcd1602_data[2] * 100 +
				  dht11_lcd1602_data[1] * 10 +
				  dht11_lcd1602_data[0],
		  10);
		if (!toggle) {
			I2C_LCD1602_WriteChar(1, 15, 0x5c);
			toggle = 1;
		}
		else {
			I2C_LCD1602_WriteChar(1, 15, 0x20);
			toggle = 0;
		}
		_delay_ms(1100);
	}
}
