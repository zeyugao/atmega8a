#ifndef atmega8a_i2c_pcf8574t_h
#define atmega8a_i2c_pcf8574t_h

#ifndef BYTE
#define BYTE unsigned char
#endif

BYTE I2C_WRITE_PCF8574(BYTE sla_addr, BYTE bdata);

#endif // atmega8a_i2c_pcf8574t_h