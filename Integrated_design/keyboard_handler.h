#ifndef KEYBOARD_HANDLER
#define KEYBOARD_HANDLER


void (*f_callback[10])(unsigned char);

unsigned char callback_count = 0;
void register_callback(void (*f)(unsigned char)) {
	f_callback[callback_count++] = f;
}

#endif // KEYBOARD_HANDLER