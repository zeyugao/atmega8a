
#include "hc_sr04.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

unsigned int read_hc_sr04() {
	unsigned int distance = 0;
	BYTE tmp_DDRB;
	tmp_DDRB = DDRB;
	cli();

	DDRB = (1 << DDB6);
	PORTB |= (1 << PORTB6);
	_delay_us(20);
	PORTB &= ~(1 << PORTB6);

	TCCR1B = 0x00;
	TCNT1 = 0x00;
	TCCR1A = 0x00;
	while (!(PINB & (1 << PORTB7)))
		;
	TCCR1B = 0x01;
	while (PINB & (1 << PORTB7))
		;

	TCCR1B = 0x00;
	distance = TCNT1;

	sei();
	DDRB = tmp_DDRB;
	distance = distance / 100 * 17;
	return distance;
}