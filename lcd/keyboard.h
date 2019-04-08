#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif
#include <util/delay.h>

#define line_1 1 << PORTB2
#define line_2 1 << PORTB3
#define line_3 1 << PORTB4
#define line_4 1 << PORTB5

unsigned char prev_status[16] = { 0 };
unsigned char clicked[16] = { 0 };


inline unsigned char get_num(unsigned char input, unsigned char line) {
	switch (input) {
		case 0x0E:
			return 1 + line * 4;
		case 0x0D:
			return 0 + line * 4;
		case 0x0B:
			return 2 + line * 4;
		case 0x07:
			return 3 + line * 4;
		default:
			return 16;
	}
}

unsigned char num_to_line[] = {
	line_1, line_2, line_3, line_4
};
unsigned char get_first_click() {
	unsigned char i = 0;
	for (; i < 16; i++) {
		if (clicked[i]) {
			return i;
		}
	}
	return 16;
}

inline void clear_click(unsigned char line) {
	unsigned char i = line * 4;
	for (; i < (line + 1) * 4; i++) {
		clicked[i] = 0;
	}
}

inline void copy(unsigned char* des, unsigned char* src, unsigned char n) {
	unsigned char i = 0;
	for (; i < n; i++) {
		des[i] = src[i];
	}
}

void scan_click() {
	copy(prev_status, clicked, 16);

	unsigned char line = 0;
	for (; line < 4; line++) {
		PORTB = ~(num_to_line[line]);
		_delay_ms(1);
		unsigned char col_in = PINC & 0x0f;
		unsigned char x = get_num(col_in, line);

		clear_click(line);

		if (x != 16) {
			clicked[x] = 1;
		}
	}
}

unsigned char get_click() {
	scan_click();

	unsigned char x = get_first_click();

	if (clicked[x] && !prev_status[x]) {
		return x;
	}
	else {
		return 16;
	}
}

#endif // KEYBOARD_H