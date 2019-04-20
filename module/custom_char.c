
#include "custom_char.h"

#define OFFSET(p, n) ((1 << (4 - n)) * (p[n]))
#define PIXEL_MAP(p) (OFFSET(p, 0) | OFFSET(p, 1) | OFFSET(p, 2) | OFFSET(p, 3) | OFFSET(p, 4))

unsigned char pixel_map_to_data(unsigned char map[]) {
	return PIXEL_MAP(map);
}