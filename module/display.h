#ifndef DISPLAY_H
#define DISPLAY_H

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif
#include <util/delay.h>

#define DIS_LINE_A 1 << PORTD0
#define DIS_LINE_B 1 << PORTD1
#define DIS_LINE_C 1 << PORTD2
#define DIS_LINE_D 1 << PORTD3
#define DIS_LINE_E 1 << PORTD4
#define DIS_LINE_F 1 << PORTD5
#define DIS_LINE_G 1 << PORTD6
#define DIS_LINE_DP 1 << PORTD7
#define DIS_LINE_4 1 << PORTB0
#define DIS_LINE_3 1 << PORTB1
#define DIS_LINE_2 1 << PORTB6
#define DIS_LINE_1 1 << PORTB7

#define NUM_1 DIS_LINE_B | DIS_LINE_C
#define NUM_2 DIS_LINE_A | DIS_LINE_B | DIS_LINE_G | DIS_LINE_E | DIS_LINE_D
#define NUM_3 DIS_LINE_A | DIS_LINE_B | DIS_LINE_G | DIS_LINE_C | DIS_LINE_D
#define NUM_4 DIS_LINE_F | DIS_LINE_G | DIS_LINE_B | DIS_LINE_C
#define NUM_5 DIS_LINE_A | DIS_LINE_F | DIS_LINE_G | DIS_LINE_C | DIS_LINE_D
#define NUM_6 DIS_LINE_A | DIS_LINE_F | DIS_LINE_G | DIS_LINE_E | DIS_LINE_C | DIS_LINE_D
#define NUM_7 DIS_LINE_A | DIS_LINE_B | DIS_LINE_C
#define NUM_8 DIS_LINE_A | DIS_LINE_B | DIS_LINE_C | DIS_LINE_D | DIS_LINE_E | DIS_LINE_F | DIS_LINE_G
#define NUM_9 DIS_LINE_A | DIS_LINE_B | DIS_LINE_C | DIS_LINE_D | DIS_LINE_F | DIS_LINE_G
#define NUM_0 DIS_LINE_A | DIS_LINE_B | DIS_LINE_C | DIS_LINE_D | DIS_LINE_E | DIS_LINE_F
#define ALPHA_A DIS_LINE_A | DIS_LINE_B | DIS_LINE_C | DIS_LINE_E | DIS_LINE_F | DIS_LINE_G
#define ALPHA_B DIS_LINE_C | DIS_LINE_D | DIS_LINE_E | DIS_LINE_F | DIS_LINE_G
#define ALPHA_C DIS_LINE_A | DIS_LINE_D | DIS_LINE_E | DIS_LINE_F
#define ALPHA_D DIS_LINE_B | DIS_LINE_C | DIS_LINE_D | DIS_LINE_E | DIS_LINE_G
#define ALPHA_E DIS_LINE_A | DIS_LINE_D | DIS_LINE_E | DIS_LINE_F | DIS_LINE_G
#define ALPHA_F DIS_LINE_A | DIS_LINE_E | DIS_LINE_F | DIS_LINE_G

unsigned char num_table[] = {
	NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, ALPHA_A, ALPHA_B, ALPHA_C, ALPHA_D, ALPHA_E, ALPHA_F
};

unsigned char display_line_table[] = {
	DIS_LINE_1, DIS_LINE_2, DIS_LINE_3, DIS_LINE_4
};

inline void enable_displayer() {
	DDRB = DIS_LINE_1 | DIS_LINE_2 | DIS_LINE_3 | DIS_LINE_4;
	DDRD = 0xFF;
}

inline static void display(unsigned int num, int decimal) {
	decimal = decimal > 16 ? 16 : decimal;
	decimal = decimal < 2 ? 2 : decimal;
	char i = 3;
	do {
		PORTD = num_table[num % decimal];
		PORTB = ~(display_line_table[i]);
		_delay_ms(1);
		i -= 1;
		num /= decimal;
	} while (num && i >= 0);
}

#endif // DISPLAY_H