#include <avr/io.h>
#include <util/delay.h>

void LED(int percent,int type){
	PORTD = 0;
	for(int i = 0;i< 100 - percent;i++){
		_delay_us(1);
	}
	PORTD = 0;
	switch(type){
		case 0:PORTD = 1<<PORTD0;break;
		case 1:PORTD = 1<<PORTD1;break;
		case 2:PORTD = 1<<PORTD2;break;
	}
	for(int i = 0;i< percent;i++){
		_delay_us(1);
	}
}

int main(void)
{
	DDRD = 1<<PORTD0|1<<PORTD1|1<<PORTD2;
    /* Replace with your application code */
	int count = 0;
    while (1) 
    {
		for(int i = 0;i<200;i++){
			for(int j = 0;j<10;j++){
				LED(i<100?i:200-i,count);
			}
		}
		count++;
		count %= 3;
    }
}
