#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

unsigned char get_click();
void enable_keyboard();

#endif // KEYBOARD_H