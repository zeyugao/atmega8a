#ifndef F_CPU
#define F_CPU 8000000L
#endif

#include "../module/hc_sr04.h"
#include "../module/i2c_lcd1602.h"
#include "../module/display.h"

int main() {
	unsigned int result;
	char res_c[5];
	enable_displayer();
	I2C_LCD1602_Init();

	unsigned int r;
	res_c[4] = '\0';
	while (1) {
		result = ReadHCSR4();
		r = result;

		for (int i = 3; i >= 0; i--) {
			res_c[i] = result % 10 + '0';
			result /= 10;
		}
		I2C_LCD1602_WriteString(0, 0, "Distance: ");
		I2C_LCD1602_WriteString(0, 12, res_c);
		_delay_ms(200);
	}
	return 0;
}