/*
ID: wentcui1
LANG: C
TASK: pprime
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define SIZE int
#define LEN sizeof(SIZE) * 8

FILE *fout;


int isPalindrome(int x) {
    int factor_h = 1, factor_t = 10;

    while(x / factor_h >= 10) {
        factor_h *= 10;
    }

    while (x >= 1) {
        int h = x / factor_h;
        int t = x % factor_t;

        if (t != h)
            return 0;

        x %= factor_h;
        x /= factor_t;

        factor_h /= 100;
    }
    return 1;
}

void setbit(SIZE map[], int pos) {
	int num = pos / LEN;
	int offset = pos % LEN;
	SIZE v = (1 << offset);
	map[num] |= v;
}

int checkbit(SIZE map[], int pos) {
	int num = pos / LEN;
	int offset = pos % LEN;
	SIZE v = (1 << offset);
	return (map[num] & v);
}

void gen_prime(int start, SIZE *map, int n) {
	int i, j;
	for(i = 2; i <= n; i++) {
		if (checkbit(map, i)) continue;
		if (i >= start && isPalindrome(i)) {
			fprintf(fout, "%d\n", i);
		}
		for(j = 2; i * j <= n; j++) {
			setbit(map, i * j);
		}
	}
}


main()
{
	FILE *fin = fopen("pprime.in", "r");
	fout = fopen("pprime.out", "w");
	int start, end, i;
	fscanf(fin, "%d %d", &start, &end);
	SIZE *map = (SIZE *)malloc(sizeof(SIZE) * ((end + 1) / LEN + 1));
	if (!map)
		printf("BAD ALLOC\n");
	memset(map, 0, sizeof(SIZE) * ((end + 1) / LEN + 1));
	gen_prime(start, map, end);

	return 0;
}
