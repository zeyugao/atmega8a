#ifndef HC_HR04_H
#define HC_HR04_H
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif
#ifndef BYTE
#define BYTE unsigned char
#endif

unsigned int ReadHCSR4() {
	unsigned int distance = 0;
	BYTE tmp_DDRC;
	tmp_DDRC = DDRC;
	cli();

	DDRC = (1 << 1);
	PORTC |= (1 << PORTC1);
	_delay_us(20);
	PORTC &= !(1 << PORTC1);

	TCCR1B = 0x00;
	TCNT1 = 0x00;
	TCCR1A = 0x00;
	while (!(PINC & 0x01))
		;
    TCCR1B = 0x01;
	while (PINC & 0x01)
		;

	TCCR1B = 0x00;	
    distance = TCNT1;

	sei();
	DDRC = tmp_DDRC;
	distance = distance * 17 / 100;
	return distance;
}

#endif // HC_HR04_H