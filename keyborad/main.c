/*
 * keyboard/main.c
 *
 * Created: 2019/3/30 10:45:58
 * Author : Elsa
 */

#ifndef F_CPU
#define F_CPU 8000000L

#endif

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif
#include <util/delay.h>

#define a 1 << PORTD0
#define b 1 << PORTD1
#define c 1 << PORTD2
#define d 1 << PORTD3
#define e 1 << PORTD4
#define f 1 << PORTD5
#define g 1 << PORTD6
#define dp 1 << PORTD7
#define _4 1 << PORTB0
#define _3 1 << PORTB1
#define _2 1 << PORTB6
#define _1 1 << PORTB7

#define line_1 1 << PORTB2
#define line_2 1 << PORTB3
#define line_3 1 << PORTB4
#define line_4 1 << PORTB5

#define NUM_1 b | c
#define NUM_2 a | b | g | e | d
#define NUM_3 a | b | g | c | d
#define NUM_4 f | g | b | c
#define NUM_5 a | f | g | c | d
#define NUM_6 a | f | g | e | c | d
#define NUM_7 a | b | c
#define NUM_8 a | b | c | d | e | f | g
#define NUM_9 a | b | c | d | f | g
#define NUM_0 a | b | c | d | e | f
#define ALPHA_A a | b | c | e | f | g
#define ALPHA_B c | d | e | f | g
#define ALPHA_C a | d | e | f
#define ALPHA_D b | c | d | e | g
#define ALPHA_E a | d | e | f | g
#define ALPHA_F a | e | f | g

unsigned char num_table[] = {
    NUM_0, NUM_1, NUM_2, NUM_3,
    NUM_4, NUM_5, NUM_6, NUM_7,
    NUM_8, NUM_9, ALPHA_A, ALPHA_B,
    ALPHA_C, ALPHA_D, ALPHA_E, ALPHA_F
};

unsigned char display_table[] = {
    _1, _2, _3, _4
};

unsigned char code_to_real_num[] = {
    1, 2, 3, 11, //1、2、3、加 - 0 1 2 3
    4, 5, 6, 12, //4、5、6、减 - 4 5 6 7
    7, 8, 9, 13, //7、8、9、乘 - 8 9 10 11
    14, 0, 15, 16 //归0、0、等于、除 - 12 13 14 15
};

struct num_to_display_struct {
    char dis[4];
    unsigned char dis_num[4];
};

struct num_to_display_struct num_to_display(int num)
{
    struct num_to_display_struct r = { 0 };
    int i = 3;
    r.dis[3] = 1;
    while (num) {
        r.dis[i] = 1;
        r.dis_num[i] = num % 10;
        i -= 1;
        num /= 10;
    }
    return r;
}

unsigned char prev_status[16] = { 0 };
unsigned char clicked[16] = { 0 };

inline unsigned char get_num(unsigned char input, unsigned char line)
{
    switch (input) {
    case 0x0E:
        return 1 + line * 4;
    case 0x0D:
        return 0 + line * 4;
    case 0x0B:
        return 2 + line * 4;
    case 0x07:
        return 3 + line * 4;
    default:
        return 16;
    }
}

unsigned char num_to_line[] = {
    line_1, line_2, line_3, line_4
};
unsigned char get_first_click()
{
    unsigned char i = 0;
    for (; i < 16; i++) {
        if (clicked[i]) {
            return i;
        }
    }
    return 16;
}

inline void clear_click(unsigned char line)
{
    unsigned char i = line * 4;
    for (; i < (line + 1) * 4; i++) {
        clicked[i] = 0;
    }
}

inline void copy(unsigned char* des, unsigned char* src, unsigned char n)
{
    unsigned char i = 0;
    for (; i < n; i++) {
        des[i] = src[i];
    }
}

void get_click()
{
    copy(prev_status, clicked, 16);

    unsigned char line = 0;
    for (; line < 4; line++) {
        PORTB = ~(num_to_line[line]);
        _delay_ms(1);
        unsigned char col_in = PINC & 0x0f;
        unsigned char x = get_num(col_in, line);

        clear_click(line);

        if (x != 16) {
            clicked[x] = 1;
        }
    }
}

void display(int num)
{
    struct num_to_display_struct r = num_to_display(num);
    unsigned char i = 3;
    while (r.dis[i] == 1) {
        PORTD = num_table[r.dis_num[i]];
        PORTB = ~(display_table[i]);
        _delay_ms(2);
        i -= 1;
    }
}

int main(void)
{
    DDRB = 0xff;
    PORTB = 0x3c;
    DDRC = 0;
    PORTC = 0xff;
    DDRD = 0xff;
    /* Replace with your application code */

    int aa = 0, bb = 0;

    unsigned char input_a = 1, input_b = 0;
    unsigned char inputing = 16;
    unsigned char plus = 0, multiply = 0, minus = 0, divide = 0;
    int to_display = 0;
    while (1) {
        get_click();

        if (input_a) {
            inputing = get_first_click();
            if (clicked[inputing] && !prev_status[inputing]) {
                inputing = code_to_real_num[inputing];
                if (inputing < 10) {
                    aa = aa * 10 + inputing;
                }
                aa %= 9999;
                to_display = aa;
            }
        }

        if (input_b) {
            inputing = get_first_click();
            if (clicked[inputing] && !prev_status[inputing]) {
                inputing = code_to_real_num[inputing];
                if (inputing < 10) {
                    bb = bb * 10 + inputing;
                }
                bb %= 9999;
                to_display = bb;
            }
        }

        // plus
        if (clicked[3]) {
            input_a = 0;
            input_b = 1;
            plus = 1;
            to_display = bb;
        }
        //minus
        if (clicked[7]) {
            input_a = 0;
            input_b = 1;
            minus = 1;
            to_display = bb;
        }

        // multiply
        if (clicked[11]) {
            input_a = 0;
            input_b = 1;
            multiply = 1;
            to_display = bb;
        }
        // divide
        if (clicked[15]) {
            input_a = 0;
            input_b = 1;
            divide = 1;
            to_display = bb;
        }

        // clear
        if (clicked[12]) {
            aa = 0;
            bb = 0;
            multiply = 0;
            plus = 0;
            input_a = 1;
            input_b = 0;
            minus = 0;
            divide = 0;
            to_display = aa;
        }

        // equal
        if (clicked[14]) {
            if (plus) {
                to_display = aa + bb;
            } else if (multiply) {
                to_display = aa * bb;
            } else if (minus) {
                if (aa > bb) {
                    to_display = aa - bb;
                } else {
                    to_display = bb - aa;
                }
            } else {
                if (aa == 0 || bb == 0) {
                    to_display = 0;
                } else if (aa > bb) {
                    to_display = aa / bb;
                } else {
                    to_display = bb / aa;
                }
            }
        }
        to_display %= 9999;
        display(to_display);
    }
}
