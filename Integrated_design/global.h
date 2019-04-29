#ifndef CONST_H
#define CONST_H

#define GLOBAL_HOME 15

#define HOME -1
#define SNAKE 0
#define HC_SR04 1
#define DHT11 2
#define BOSS_MODE 3

char CURRENT_PAGE = HOME;

enum {
	buzzer = 0,
	flicker,
	none
};

unsigned char BOSS_MODE_ALERT_TYPE = none;

#endif // CONST_H