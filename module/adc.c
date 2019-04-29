#include "adc.h"

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

void adc_init(unsigned char ch) {
	ADMUX = (1 << REFS0) | ch;
	ADCSRA = (1 << ADEN) | (1 << ADFR) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADSC);
	DDRC = 0;
}

void read_adc(unsigned char *dh, unsigned char *dl) {
	while (!(ADCSRA & (1 << ADIF)))
		;
	*dl = ADCL;
	*dh = ADCH;
}