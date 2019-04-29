#include "snake.h"
#include "../module/i2c_lcd1602.h"
#include "../module/custom_char.h"
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


int snake_body_map[16 * 5][8 * 2];

void convert_snake_to_map() {
	for (int i = 0; i < 16 * 5; i++) {
		for (int j = 0; j < 8 * 2; j++) {
			snake_body_map[i][j] = 0;
		}
	}
	if (head < tail) {
		for (int i = head; i < tail; i++) {
			snake_body_map[queue[i]->x][queue[i]->y] = 1;
		}
	}
	else {
		for (int i = 0; i < tail; i++) {
			snake_body_map[queue[i]->x][queue[i]->y] = 1;
		}
		for (int i = head; i < QUEUE_SIZE; i++) {
			snake_body_map[queue[i]->x][queue[i]->y] = 1;
		}
	}
}

void display() {
	convert_snake_to_map();
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 2; j++) {
			int t[8][5];
			for (int n = 0; n < 8; n++) { // row
				for (int m = 0; m < 5; m++) {
					t[n][m] = snake_body_map[i * 5 + m][j * 8 + n];
				}
			}
			char output[8];
			gen_bitmap(t, output);
			I2C_LCD1602_CreateChar(0, output);
			I2C_LCD1602_WriteChar(j, i, output);
		}
	}
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