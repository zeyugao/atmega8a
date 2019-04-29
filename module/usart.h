#ifndef USART_H
#define USART_H

#define F_CPU 8000000UL
#define BAUD 9600UL
#define MYUBRR F_CPU / 16UL / BAUD - 1

void usart_init(unsigned int ubrr_val);
void usart_send(unsigned char data);
unsigned char usart_receive(void);
void usart_flush(void);
void usart_send_array(unsigned char* data, int len);
void usart_send_string(char* str);

#endif // USART_H