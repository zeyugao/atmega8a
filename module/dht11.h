#ifndef HDT11_H
#define HDT11_H

#include <avr/io.h>

#ifndef BYTE
#define BYTE unsigned char
#endif

BYTE dht11_data[4];

BYTE *get_dht11_data() {
	return dht11_data;
}

BYTE ByteReadDHT11() {
	BYTE pw_counter, i, bytedata = 0, onebit;
	for (i = 0; i < 8; i++) {
		pw_counter = 1;
		while (!(PINB & (1<<PORTB0))) {
			pw_counter++;
			if (!pw_counter)
				break;
		}

		_delay_us(30);
		onebit = 0;

		if (PINB & (1<<PORTB0))
			onebit = 1;

		pw_counter = 1;
		while (PINB & (1<<PORTB0)) {
			pw_counter++;
			if (pw_counter == 1)
				break;
		}
		bytedata <<= 1;
		bytedata |= onebit;
	}
	return bytedata;
}

void DHT11_run(void) {
	BYTE pw_counter;
	BYTE humidity, H_num;
	BYTE temperature, T_num;
	BYTE parity;

	dht11_data[3] = 0;
	dht11_data[2] = 0;
	dht11_data[1] = 0;
	dht11_data[0] = 0;

	DDRB |= 1<<PORTB0;
	PORTB &= ~(1<<PORTB0);
	_delay_ms(20);

	PORTB |= 1<<PORTB0;
	DDRB &= ~(1<<PORTB0);

	_delay_us(40);
	if (PINC & 0x08)
		return;

	pw_counter = 1;
	while (!(PINB & (1<<PORTB0))) {
		pw_counter++;
		if (!pw_counter)
			return;
	}
	pw_counter = 1;
	while (PINB & (1<<PORTB0)) {
		pw_counter++;
		if (!pw_counter)
			return;
	}
	humidity = ByteReadDHT11();
	H_num = ByteReadDHT11();
	temperature = ByteReadDHT11();
	T_num = ByteReadDHT11();
	parity = ByteReadDHT11();

	if (parity == (humidity + temperature + H_num + T_num)) {
		dht11_data[3] = temperature / 10;
		dht11_data[2] = temperature % 10;
		dht11_data[1] = humidity / 10;
		dht11_data[0] = humidity % 10;
	}
}
#endif // HDT11_H
