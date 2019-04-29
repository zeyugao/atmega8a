
#include "custom_char.h"

#define OFFSET(p, n) ((1 << (4 - n)) * (p[n]))
#define PIXEL_MAP(p) (OFFSET(p, 0) | OFFSET(p, 1) | OFFSET(p, 2) | OFFSET(p, 3) | OFFSET(p, 4))

unsigned char pixel_map_to_data(unsigned char map[5]) {
	return PIXEL_MAP(map);
}

void gen_bitmap(unsigned char map[8][5], unsigned char output[8]) {
	for (int i = 0; i < 8; i++) {
		output[i] = pixel_map_to_data(map[i]);
	}
}