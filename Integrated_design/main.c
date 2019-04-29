#include "global.h"
#include "menu.h"
#include "snake.h"
#include "boss_mode.h"
#include "hc_sr04.h"

int main() {
	enable_stepper();
	enable_keyboard();

	while (1) {
		switch (CURRENT_PAGE) {
			case HOME:
				menu();
				break;
			case SNAKE:
				snake();
				break;
			case HC_SR04:
				hc_sr04();
				break;
			case DHT11:
				dht11();
				break;
			case BOSS_MODE:
				boss_mode();
				break;
			default:
				break;
		}
	}
}