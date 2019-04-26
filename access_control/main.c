#define F_CPU 1000000UL

#include <util/delay.h>
#include <stdlib.h>

#include "../module/usart.h"
#include "../module/i2c_lcd1602.h"
#include "../module/keyboard.h"

#include "global.h"

#include "welcome.h"
#include "password.h"

unsigned char CURRENT_STAGE = WELCOME;

int main() {
	I2C_LCD1602_Init();
	enable_keyboard();
	while (1) {
		switch (CURRENT_STAGE) {
			case WELCOME:
				CURRENT_STAGE = welcome();
				break;
			case PASSWORD:
				CURRENT_STAGE = password();
				break;
			case FACE_UNLOCK:
				break;
			case PASS:
				break;
			default:
				break;
		}
	}

	return 0;
}