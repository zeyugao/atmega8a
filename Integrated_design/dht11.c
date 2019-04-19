#include "dht11.h"
#include "../module/keyboard.h"
#include "../module/i2c_lcd1602.h"
#include "global.h"
#include "util/delay.h"
void dht11() {
	unsigned char __q = 0;
	unsigned char cnt = 0;
	unsigned char key;
	BYTE *dht11_lcd1602_data;
	BYTE toggle = 0;
	while (!__q) {
		key = get_click();
		if (key == 15) {
			__q = 1;
			CURRENT_PAGE = HOME;
		}
		if (cnt > 1100) {
			cnt = 0;
			dht11_lcd1602_data = get_dht11_data();
			I2C_LCD1602_WriteString(0, 0, "Temperature :");
			I2C_LCD1602_WriteNewChar(dht11_lcd1602_data[3] + '0');
			I2C_LCD1602_WriteNewChar(dht11_lcd1602_data[2] + '0');

			I2C_LCD1602_WriteString(1, 0, "Humidity :");
			I2C_LCD1602_WriteNewChar(dht11_lcd1602_data[1] + '0');
			I2C_LCD1602_WriteNewChar(dht11_lcd1602_data[0] + '0');
			if (!toggle) {
				I2C_LCD1602_WriteChar(1, 15, 0x5c);
				toggle = 1;
			}
			else {
				I2C_LCD1602_WriteChar(1, 15, 0x20);
				toggle = 0;
			}
		}
		_delay_ms(1);
		cnt++;
	}
}