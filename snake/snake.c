#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "snake.h"
#include "light.h"
#include "../module/i2c_lcd1602.h"
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

#include <avr/io.h>
#ifndef BUILD
#include <avr/iom8a.h>
#endif

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define MAP_X 7
#define MAP_Y 7
#define QUEUE_SIZE ((MAP_X) * (MAP_Y))

char delta_x[4] = { 0, 0, -1, 1 };
char delta_y[4] = { 1, -1, 0, 0 };
unsigned char snake_body_map[7][7];
unsigned char food_x = 0, food_y = 0;

LightData data[7][7];

typedef struct {
	int x, y;
} Snake;

Snake *queue[QUEUE_SIZE] = { 0 };

/*
include start, 
but exclude end
*/
unsigned int my_random(unsigned int start, unsigned char end) {
	return (rand() % (end - start)) + start;
}

void gen_food() {
	do {
		food_x = my_random(0, MAP_X);
		food_y = my_random(0, MAP_Y);
	} while (snake_body_map[food_x][food_y]);
}

unsigned char head = 0 /*the last one*/, tail = 0 /*ahead of the first one*/;
void en_quene(Snake *p) {
	queue[tail] = p;
	tail = (tail + 1) % QUEUE_SIZE;
}

Snake *de_queue() {
	//free(queue[head]);
	int head_bak = head;
	head = (head + 1) % QUEUE_SIZE;
	return queue[head_bak];
}

void gen_display() {
	for (unsigned char i = 0; i < MAP_X; i++) {
		for (unsigned char j = 0; j < MAP_Y; j++) {
			data[i][j].on = snake_body_map[i][j];
			data[i][j].percent = 1;
		}
	}
	Snake *first = queue[(tail - 1 + QUEUE_SIZE) % QUEUE_SIZE];
	data[first->x][first->y].on = 1;
	data[first->x][first->y].percent = 3;
	data[food_x][food_y].on = 1;
	data[food_x][food_y].percent = 3;
}

unsigned char process_move(unsigned char direction) {
	Snake *first = queue[(tail - 1 + QUEUE_SIZE) % QUEUE_SIZE];
	if ((first->x + delta_x[direction] + MAP_X) % MAP_X == food_x &&
		(first->y + delta_y[direction] + MAP_Y) % MAP_Y == food_y) {
		Snake *new_part = (Snake *)malloc(sizeof(Snake));
		new_part->x = (first->x + delta_x[direction] + MAP_X) % MAP_X;
		new_part->y = (first->y + delta_y[direction] + MAP_Y) % MAP_Y;
		snake_body_map[new_part->x][new_part->y] = 1;
		en_quene(new_part);
		gen_food();
		return 1;
	}

	Snake *last = de_queue();

	snake_body_map[last->x][last->y] = 0;

	last->x = (first->x + delta_x[direction] + MAP_X) % MAP_X;
	last->y = (first->y + delta_y[direction] + MAP_Y) % MAP_Y;

	if (snake_body_map[last->x][last->y]) {
		return 0; // collision detected
	}

	snake_body_map[last->x][last->y] = 1;
	en_quene(last);

	return 1;
}

unsigned char get_input() {
	for (unsigned char i = 0; i <= 3; i++) {
		if (PINC & (1 << i)) {
			return i;
		}
	}
	return 4;
}

unsigned char check_conflict(unsigned char previous_towards, unsigned char new_towards) {
	/*if (previous_towards == UP && new_towards == DOWN) {
		return 1;
	}
	else if (previous_towards == DOWN && new_towards == UP) {
		return 1;
	}
	else if (previous_towards == LEFT && new_towards == RIGHT) {
		return 1;
	}
	else if (previous_towards == RIGHT && new_towards == LEFT) {
		return 1;
	}*/
	if ((previous_towards + new_towards == 1) || (previous_towards + new_towards == 5))
		return 1;
	return 0;
}

void snake() {
	memset(data, 0, sizeof(data));
	unsigned char __q = 0;
	unsigned char towards = UP, tmp_towards;

	Snake *part = (Snake *)malloc(sizeof(Snake));
	part->x = my_random(0, MAP_X);
	part->y = my_random(0, MAP_Y);

	snake_body_map[part->x][part->y] = 1;
	en_quene(part);

	gen_food();
	gen_display();

	unsigned char cnt = 0;
	while (1) {
		tmp_towards = get_input();
		if (tmp_towards <= 3)
			if (!check_conflict(towards, tmp_towards))
				towards = tmp_towards;
		if (cnt >= 40) {
			if (!process_move(towards)) {
				// game over
				break;
			}
			cnt = 0;
		}
		else {
			cnt++;
			_delay_ms(1);
		}
		gen_display();
	}
}