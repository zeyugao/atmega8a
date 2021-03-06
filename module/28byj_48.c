#include "28byj_48.h"
#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

#include <util/delay.h>


const BYTE stepper_ph[3][8] = { { 0x01, 0x03, 0x02, 0x66, 0x04, 0x0C, 0x08, 0x09 },
	{ 0x03, 0x06, 0x0C, 0x09 },
	{ 0x01, 0x02, 0x04, 0x08 } };

void enable_stepper() {
	DDRD = 0x0f;
}

BYTE stepper_index = 0;
void run_stepper(BYTE phase, BYTE dir, unsigned int step) {
	BYTE ph = phase ? 0x03 : 0x07;
	BYTE inc = dir ? 0x01 : ph;
	unsigned int i;
	for (i = 0; i < step; i++) {
		stepper_index += inc;
		stepper_index &= ph;
		PORTD = stepper_ph[phase][stepper_index];
		switch (phase) {
			case 0:
				_delay_us(900);
				break;
			case 1:
				_delay_us(1600);
				break;
			case 2:
				_delay_us(2000);
				break;
			default:
				break;
		}
	}
}