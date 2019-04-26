#include "welcome.h"

#include <util/delay.h>
#include "../module/i2c_lcd1602.h"
#include "../module/keyboard.h"
#include "global.h"

unsigned char welcome() {
	char *welcome_str = "Welcome to Access Control    ";
	unsigned char i = 0;
	I2C_LCD1602_WriteString(0, 1, "Press ENTER");
	unsigned char count = 0;
	unsigned char key = 16;
	while (1) {
		key = get_click();
		if (key == 15) {
			return PASSWORD;
		}

		I2C_LCD1602_WriteString(0, 0, welcome_str + i);

		if (count == 10) {
			i++;
			i %= 12;
			count = 0;
		}
		else {
			count++;
			_delay_ms(10);
		}
	}
}