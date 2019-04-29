#ifndef ADC_H
#define ADC_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

void adc_init(unsigned char ch);
void read_adc(unsigned char *dh, unsigned char *dl);

#endif // ADC_H