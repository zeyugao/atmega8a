#include "snake.h"
#include "../module/i2c_lcd1602.h"
#include <stdlib.h>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define QUEUE_SIZE 1441

int delta_x[4] = { 0, 0, -1, 1 };
int delta_y[4] = { -1, 1, 0, 0 };

struct snake_part {
	int x, y;
};

struct snake_part *queue[QUEUE_SIZE] = { 0 };

unsigned char towards;

// TODO
void display() {
}

// TODO
int random() {
	return 0;
}

int head = 0, tail = 0;
void en_quene(struct snake_part *p) {
	queue[tail] = p;
	tail = (tail + 1) % QUEUE_SIZE;
}
void de_queue() {
	free(queue[head]);
	head = (head + 1) % QUEUE_SIZE;
}

void snake() {
	unsigned char __q = 0;
	towards = UP;

	struct snake_part *part = (struct snake_part *)malloc(sizeof(struct snake_part));
	part->x = random();
	part->y = random();
	en_quene(part);
	while (!__q) {

	}
}