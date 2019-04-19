#include "../module/28byj_48.h"

int main() {

	DDRC = 0x0f;
	while (1) {
		for (int i = 0; i < 4096; i++) {
			for (int j = 0; j < i; j++) {
				run_stepper(0, i & 1, j);
			}
		}
	}
	return 0;
}