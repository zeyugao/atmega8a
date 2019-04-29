/*
 * display/main.c
 *
 * Created: 2019/3/30 8:38:35
 * Author : Elsa
 */ 

#ifndef F_CPU
#define F_CPU 8000000L

#endif

#include <avr/io.h>
#include <util/delay.h>

#define a 1<<PORTD0
#define b 1<<PORTD1
#define c 1<<PORTD2
#define d 1<<PORTD3
#define e 1<<PORTD4
#define f 1<<PORTD5
#define g 1<<PORTD6
#define dp 1<<PORTD7
#define _4 1<<PORTB0
#define _3 1<<PORTB1
#define _2 1<<PORTB6
#define _1 1<<PB7

#define NUM_1 b|c
#define NUM_2 a|b|g|e|d
#define NUM_3 a|b|g|c|d
#define NUM_4 f|g|b|c
#define NUM_5 a|f|g|c|d
#define NUM_6 a|f|g|e|c|d
#define NUM_7 a|b|c
#define NUM_8 a|b|c|d|e|f|g
#define NUM_9 a|b|c|d|f|g
#define NUM_0 a|b|c|d|e|f
#define ALPHA_A a|b|c|e|f|g
#define ALPHA_B c|d|e|f|g
#define ALPHA_C a|d|e|f
#define ALPHA_D b|c|d|e|g
#define ALPHA_E a|d|e|f|g
#define ALPHA_F a|e|f|g

unsigned char num_table[] = {
	NUM_0,NUM_1,NUM_2,NUM_3,
	NUM_4,NUM_5,NUM_6,NUM_7,
	NUM_8,NUM_9,ALPHA_A,ALPHA_B,
	ALPHA_C,ALPHA_D,ALPHA_E,ALPHA_F
};

unsigned char display_table[] = {
	0,_1,_2,_3,_4
};

struct num_to_display_struct{
	char dis[5];
	unsigned char dis_num[5];
	};

struct num_to_display_struct num_to_display(int num){
	struct num_to_display_struct r = {0};
	int i = 4;
	r.dis[4] = 1;
	while(num){
		r.dis[i] = 1;
		r.dis_num[i] = num % 16;
		i-=1;
		num /=16;
	}
	return r;
}

inline unsigned char get_click(){
	
}

int main(void)
{
	DDRB = _1|_2|_3|_4;
	
	DDRD = 0xFF;
	
	
	
	unsigned char i = 0;
	unsigned char count = 0;
	int num = 0;
    /* Replace with your application code */
    while (1) 
    {
		struct num_to_display_struct r = num_to_display(num);
		i = 4;
		while(r.dis[i] == 1){
			PORTD = num_table[r.dis_num[i]];
			PORTB = ~(display_table[i]);
			_delay_ms(10);
			i-=1;
			
			if (num%4 == 0){
				PORTD = dp;
				PORTB = ~(_4|_3);
			}
			else if (num%4 == 1){
				PORTD = dp;
				PORTB = ~(_3);
			}
			else if(num%4 == 2){
				PORTD = dp;
				PORTB = ~(_4);
			}
			else{
			}
		}
		
		count++;
		if (count >= 50){
			count -=50;
			num++;
		}
		
		num %= 10000;
		
		
		
    }
}

