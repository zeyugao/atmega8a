#ifndef _28BYJ_48_H
#define _28BYJ_48_H

#ifndef BYTE
#define BYTE unsigned char
#endif

void run_stepper(BYTE phase, BYTE dir, unsigned int step);
void enable_stepper();

#endif //_28BYJ_48_H
