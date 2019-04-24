#ifndef F_CPU
#define F_CPU 1000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "../module/i2c_lcd1602.h"
#include "video_context.h"

int video_frame_len = sizeof(video_context) / sizeof(unsigned char);

int main() {
	I2C_LCD1602_Init();

	video_frame_len /= 64;
	while (1) {
		for (int i = 0; i < video_frame_len; i++) {
			const unsigned char *ptr = (const unsigned char *)&video_context[i];

			for (unsigned char r = 0; r < 2; r++) {
				for (unsigned char c = 0; c < 4; c++) {
					unsigned char pixel[8];
					for (unsigned char p = 0; p < 8; p++) {
						pixel[p] = pgm_read_byte(ptr++);
					}
					I2C_LCD1602_CreateChar(r * 4 + c, pixel);
					I2C_LCD1602_WriteChar(r, c, r * 4 + c);
				}
			}
			_delay_ms(405);
		}
	}
	return 0;
}