#include "boss_mode.h"
#include "global.h"

#include <util/delay.h>
#include "../module/keyboard.h"
#include "../module/i2c_lcd1602.h"
#include "../module/hc_sr04.h"

#define ON 1
#define OFF 0

char *display_type[] = {
	"Buzzer",
	"Flicker",
	"None"
};
unsigned char type_len = sizeof(display_type) / sizeof(char *);

unsigned char current_selected_type = buzzer;

void display() {
	I2C_LCD1602_ClearLine(1);
	I2C_LCD1602_WriteString(1, 2, display_type[current_selected_type]);
}

unsigned char viewing_current_type = 0;

void display_current_type() {
	I2C_LCD1602_ClearAll();
	I2C_LCD1602_WriteString(0, 0, "Current type:");
	I2C_LCD1602_WriteString(1, 2, display_type[BOSS_MODE_ALERT_TYPE]);
}

void boss_mode() {
	unsigned char __q = 0;
	unsigned char key;
	I2C_LCD1602_ClearAll();
	I2C_LCD1602_WriteString(0, 0, "Boss Mode");
	while (!__q) {
		key = get_click();
		if (key == HOME) {
			CURRENT_PAGE = HOME;
			__q = 1;
		}
		else if (key == 7) { // Up
			current_selected_type--;
			current_selected_type = (current_selected_type + type_len) % type_len;
		}
		else if (key == 11) { // Down
			current_selected_type++;
			current_selected_type = current_selected_type % type_len;
		}
		else if (key == 14) { // OK
			BOSS_MODE_ALERT_TYPE = current_selected_type;
			I2C_LCD1602_ClearAll();
			I2C_LCD1602_WriteString(0, 0, "OK!");
			_delay_ms(1000);
		}
		else if (key == 0) { // View current type
			viewing_current_type = !viewing_current_type;
		}
		if (!viewing_current_type)
			display();
		else
			display_current_type();
	}
}

//TODO
unsigned char check() {
}