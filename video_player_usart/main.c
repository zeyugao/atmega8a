
#define F_CPU 1000000UL

#include <util/delay.h>
#include <stdlib.h>

#include "../module/usart.h"
#include "../module/i2c_lcd1602.h"

unsigned char frame[65];
int main() {

	I2C_LCD1602_Init();
	usart_init(MYUBRR);

	while (1) {
		unsigned char count = 0;
		while (count != 64) {
			unsigned char read_data = usart_receive();
			if (read_data == 127)
				goto exit;
			//char buffer[4];
			//itoa((int)read_data, buffer, 4);
			//I2C_LCD1602_WriteString(0, 6, "   ");
			//I2C_LCD1602_WriteString(0, 6, buffer);
			if (read_data <= 31)
				frame[count++] = read_data;
			else if (read_data <= 33)
				for (unsigned char i = 0; i < 8; i++)
					frame[count++] = (read_data == 32 ? 0 : 31);
			else if (read_data <= 35)
				for (unsigned char i = 0; i < 4; i++)
					frame[count++] = (read_data == 34 ? 0 : 31);
			else if (read_data <= 36 + 31)
				for (unsigned char i = 0; i < 3; i++)
					frame[count++] = read_data - 36;
			else
				for (unsigned char i = 0; i < 2; i++)
					frame[count++] = read_data - 36 - 32;
		}
		for (unsigned char r = 0; r < 2; r++) {
			for (unsigned char c = 0; c < 4; c++) {
				I2C_LCD1602_CreateChar(r * 4 + c, frame + r * 32 + c * 8);
				I2C_LCD1602_WriteChar(r, c, r * 4 + c);
			}
		}
		usart_send(0);
	}
exit:
	while (1) {
		I2C_LCD1602_WriteString(0, 0, "Exit");
	}
	return 0;
}