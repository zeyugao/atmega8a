#include "usart.h"

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

void usart_init(unsigned int ubrr_val) {
	UBRRH = (unsigned char)(ubrr_val >> 8);
	UBRRL = (unsigned char)(ubrr_val);
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

void usart_send(unsigned char data) {
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = data;
}

unsigned char usart_receive(void) {
	while (!(UCSRA & (1 << RXC)))
		;
	unsigned char data = UDR;
	return data;
}

void usart_flush(void) {
	unsigned char dummy;
	while (UCSRA & (1 << RXC))
		dummy = UDR;
}

void usart_send_string(char* str) {
	while (*str) {
		usart_send(*str);
		str++;
	}
}

void usart_send_array(unsigned char* data, int len) {
	for (int i = 0; i < len; i++)
		usart_send(data[i]);
}