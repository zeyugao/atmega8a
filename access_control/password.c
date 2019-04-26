#include "password.h"

#include <util/delay.h>

#include "global.h"
#include "../module/keyboard.h"
#include "../module/usart.h"
#include "../module/i2c_lcd1602.h"

unsigned char password() {
	unsigned char i = 0;
	char *prompt = "Please input your password    ";
	unsigned char count = 0;
	unsigned char key = 16;
	char display_stuff[10];
	unsigned char password_len = 0;
	while (1) {
		I2C_LCD1602_WriteString(0, 0, prompt + i);
		key = get_click();
		if (key == 15) { // press enter
			usart_send(15);
		}
		else if (key <= 9) { // input password
			usart_send(key);
			display_stuff[password_len++] = key + '0';
			display_stuff[password_len] = '\0';
		}
		else if (key == 14) { // backspace
			display_stuff[password_len] = '\0';
			password_len--;
			usart_send(14);
		}
		else if (key == 12) { //back
            I2C_LCD1602_ClearAll();
			return WELCOME;
		}
		//I2C_LCD1602_ClearLine(1);
		I2C_LCD1602_WriteString(1, 0, display_stuff);

		if (count == 10) {
			i++;
			i %= 12;
			count = 0;
		}
		else {
			count++;
			_delay_ms(5);
		}
	}
}