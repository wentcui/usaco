#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE0 73
#define TYPE1 ((1 << 9) + TYPE0)

unsigned int rec[4][4];

unsigned int getv(int x, int y, int type, unsigned int cur) {
	unsigned int base = 7, shift = (1 << 9), mask = (1 << 9) - 1;
	if (x < 0 || x >= 4 || y < 0 || y >= 4)
		return 0;
	if ((rec[x][y] & shift) != (cur & shift))
		return 0;

	return (rec[x][y] & (base << ((type - 1) * 3))) & mask;
}

int main() {
	int i, j;
	int cases, caseno = 0;
	char c,
	scanf("%d", &cases);
	getchar();
	while(cases--) {
		for(i = 0; i < 4; i++) {
			for(j = 0; j < 4; j++) {
				scanf("%c", &c);
				if ()
			}
		}
	}
}
