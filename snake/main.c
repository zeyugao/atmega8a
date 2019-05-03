#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif
#include <string.h>
#include <avr/eeprom.h>
#include <stdlib.h>

#include "../module/i2c_lcd1602.h"
#include "snake.h"
#include "light.h"

#ifndef MY_TIME_STAMP
#define MY_TIME_STAMP 197001010000
#endif

#define START_NUM 225
//unsigned char flash_count = 0;

extern LightData data[7][7];

ISR(TIMER0_OVF_vect) {
	TCNT0 = START_NUM;
	display();
}

char buffer[20];
uint32_t t;
/*
  Read random seed from eeprom and write a new random one.
*/
void init_rand() {
	uint32_t state;

	static uint32_t EEMEM sstate;

	state = eeprom_read_dword(&sstate);
	t = state;
	if ((int)(t - 65535) == 0) {
		state = (unsigned int)MY_TIME_STAMP;
	}
	srand(state);
	eeprom_write_dword(&sstate, rand());
}

int main() {
	DDRB = 0xff;
	DDRD = 0xff;
	DDRC = 0;
	init_rand();
	I2C_LCD1602_Init();

	int cnt = 0;

	TCCR0 = 0x0;
	TCNT0 = START_NUM; // start num
	TIMSK = 0x01;
	sei();
	TCCR0 = 0x05;

	snake(); // enter loop
			 // once exit the loop, it means the player failed

	while (1) {
		I2C_LCD1602_WriteString(0, 0, "Game over");
	}
}
