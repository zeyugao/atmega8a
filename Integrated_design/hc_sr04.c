#include "hc_sr04.h"
#include "../module/hc_sr04.h"
#include "../module/keyboard.h"
#include "../module/i2c_lcd1602.h"
#include "global.h"
void hc_sr04() {
	unsigned char __q = 0;
	unsigned char key;
	unsigned char cnt = 0;
	I2C_LCD1602_ClearAll();
	I2C_LCD1602_WriteString(0, 0, "Distance");
	char c[6];
	unsigned int distance;
	c[5] = '\0';
	while (!__q) {
		key = get_click();
		if (key == 15) { // exit
			__q = 1;
			CURRENT_PAGE = HOME;
		}
		if (cnt == 30) {
			cnt = 0;
			distance = read_hc_sr04();
			unsigned char i;
			for (i = 4; i >= 0; i--) {
				c[i] = distance % 10;
				distance /= 10;
				if (distance == 0) {
					break;
				}
			}
			i--;
			while (i >= 0) {
				c[i] = ' ';
				i--;
			}
			I2C_LCD1602_WriteString(1, 2, c);
		}
		cnt++;
	}
}