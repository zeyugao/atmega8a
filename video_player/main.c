#ifndef F_CPU
#define F_CPU 1000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "../module/i2c_lcd1602.h"
#include "video_context.h"

unsigned char frame[70];
int main() {
	I2C_LCD1602_Init();

	while (1) {
		const unsigned char *ptr = video_context;

		unsigned char c = pgm_read_byte(ptr++);
		while (c != 127) { // End of content
			unsigned char pos = 0;
			while (pos != 64) { // End of frame
				if (c <= 31)
					frame[pos++] = c;
				else if (c <= 33)
					for (unsigned char i = 0; i < 8; i++)
						frame[pos++] = (c == 32 ? 0 : 31);
				else if (c <= 35)
					for (unsigned char i = 0; i < 4; i++)
						frame[pos++] = (c == 34 ? 0 : 31);
				else if (c <= 36 + 31)
					for (unsigned char i = 0; i < 3; i++)
						frame[pos++] = c - 36;
				else
					for (unsigned char i = 0; i < 2; i++)
						frame[pos++] = c - 36 - 32;
				c = pgm_read_byte(ptr++);
			}

			for (unsigned char r = 0; r < 2; r++) {
				for (unsigned char c = 0; c < 4; c++) {
					I2C_LCD1602_CreateChar(r * 4 + c, frame + r * 32 + c * 8);
					I2C_LCD1602_WriteChar(r, c, r * 4 + c);
				}
			}
			_delay_ms(405);
		}
	}
	return 0;
}