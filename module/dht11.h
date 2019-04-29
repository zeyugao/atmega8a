#ifndef HDT11_H
#define HDT11_H

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

/*
data[0]: 湿度个位
data[1]: 湿度十位
data[2]: 温度个位
data[3]: 温度十位
*/
void read_dht11(unsigned char*data);

#endif // HDT11_H
