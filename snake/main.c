#include "snake.h"
#include "../module/i2c_lcd1602.h"
#include "../module/custom_char.h"
#include "../module/adc.h"
#include <stdlib.h>
#include <util/delay.h>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define MAP_X 7
#define MAP_Y 7
#define QUEUE_SIZE ((MAP_X) * (MAP_Y))

unsigned char delta_x[4] = { 0, 0, -1, 1 };
unsigned char delta_y[4] = { -1, 1, 0, 0 };
unsigned char snake_body_map[7][7];
unsigned char food_x, food_y;

typedef struct {
	unsigned int x, y;
} Snake;

Snake *queue[QUEUE_SIZE] = { 0 };

/*
include start, 
but exclude end
*/
unsigned int random(unsigned int start, unsigned char end) {
	return start < end ? (rand() + start) % (end - start) : start;
}

void gen_food() {
	do {
		food_x = random(0, MAP_X);
		food_y = random(0, MAP_Y);
	} while (snake_body_map[food_x][food_y]);
}

// TODO
void display() {
}

// TODO
unsigned char get_direction() {
}

int head = 0, tail = 0;
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

unsigned char process_move(unsigned char direction) {
	Snake *first = queue[(tail - 1 + QUEUE_SIZE) % QUEUE_SIZE];
	if (first->x + delta_x[direction] == food_x && first->y + delta_y[direction] == food_y) {
		Snake *new_part = (Snake *)malloc(sizeof(Snake));
		new_part->x = first->x + delta_x[direction];
		new_part->y = first->y + delta_y[direction];
		snake_body_map[new_part->x][new_part->y] = 1;
		en_quene(new_part);
		gen_food();
		return 0;
	}

	Snake *last = de_queue();

	snake_body_map[last->x][last->y] = 0;

	last->x = first->x + delta_x[direction];
	last->y = first->y + delta_x[direction];

	if (snake_body_map[last->x][last->y]) {
		return 0; // collision detected
	}

	snake_body_map[last->x][last->y] = 1;
	en_quene(last);

	return 1;
}

void snake() {
	unsigned char __q = 0;
	unsigned char towards = UP, tmp_towards;

	adc_init(0);
	unsigned char dh, dl;
	read_adc(&dh, &dl);
	srand((unsigned int)dh * (unsigned int)dl);

	Snake *part = (Snake *)malloc(sizeof(Snake));
	part->x = random(0, MAP_X);
	part->y = random(0, MAP_Y);
	en_quene(part);

	gen_food();

	unsigned char cnt = 0;
	while (!__q) {
		if (cnt >= 100) {
			display();
			cnt = 0;
		}
		towards = (tmp_towards = get_direction()) <= 3 ? tmp_towards : towards;
		if (!process_move(towards)) {
			// game over
			__q = 1;
		}

		display();

		_delay_ms(10);
	}
}