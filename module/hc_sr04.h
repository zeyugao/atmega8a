#ifndef HC_SR04_H
#define HC_SR04_H

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

unsigned int read_hc_sr04();

#endif // HC_SR04_H
