#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif
#include "light.h"

#define DELAY_TIME 15

extern LightData data[7][7];

void display() {
	for (unsigned char i = 0; i < 7; i++) {
		for (unsigned char j = 0; j < 7; j++) {
			LightData t = data[i][j];
			unsigned char on = t.on;
			for (unsigned char k = 0; k <= t.percent; k++) {
				PORTD = on ? ~(1 << j) : 0xff;
				PORTB = on ? (1 << i) : 0;
				_delay_us(DELAY_TIME);
				PORTD = 0xff;
				PORTB = 0;
			}
			for (unsigned char k = 0; k < 3 - t.percent; k++) {
				PORTD = 0xff;
				PORTB = 0;
				_delay_us(DELAY_TIME);
				PORTD = 0xff;
				PORTB = 0;
			}
		}
	}
}