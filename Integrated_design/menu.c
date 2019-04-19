#include "menu.h"

#include "global.h"
#include "../module/keyboard.h"
#include "../module/i2c_lcd1602.h"

char *menu_str[] = {
	"Snake",
	"HC_SR04",
	"DHT11",
	"BOSS MODE"
};

int menu_len = sizeof(menu_str) / sizeof(char *);

void click_callback(unsigned char key) {
}

void menu_init() {
	register_callback(click_callback);
}
int current_menu;
void menu() {
	I2C_LCD1602_ClearAll();
	current_menu = 0;
	I2C_LCD1602_WriteString(0, 0, "Menu");
	display_menu();
	unsigned char __q = 0;
	unsigned char key;
	while (!__q) {
		key = get_click();
		if (key == 16)
			continue;		 // No key inputed
		else if (key == 7) { // Up
			current_menu--;
			current_menu = (current_menu + menu_len) % menu_len;
		}
		else if (key == 11) { // Down
			current_menu++;
			current_menu = current_menu % menu_len;
		}
        else if(key == 14) { // OK
            CURRENT_PAGE = current_menu;
            __q = 1;
        }
        display_menu();
	}
}
void display_menu() {
	I2C_LCD1602_ClearLine(1);
	I2C_LCD1602_WriteString(1, 2, menu_str[current_menu]);
}