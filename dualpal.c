/*
ID: wentcui1
LANG: C
TASK: dualpal
*/
#include <stdio.h>

int isPalindrome(int x, int f) {
	// Start typing your Java solution below
	// DO NOT write main() function
	int factor_h = 1, factor_t = f, f2 = f * f;

	while(x / factor_h >= f) {
		factor_h *= f;
	}

	while (x > 0) {
		int h = x / factor_h;
		int t = x % factor_t;

		if (t != h)
			return -1;

		x %= factor_h;
		x /= factor_t;

		factor_h /= f2;
	}
	return 0;
}


main() {
	FILE *fin = fopen("dualpal.in", "r");
	FILE *fout = fopen("dualpal.out", "w");
	int n, start, i, count, base;
	fscanf(fin, "%d %d", &n, &start);
	while(n > 0) {
		count = 2;
		start++;
		for(base = 2; base <= 10; base++) {
			if (!isPalindrome(start, base)) {
				count--;
			}
			if (!count) {	
				fprintf(fout, "%d\n", start);
				n--;
				break;
			}
		}
	}
	exit(0);
}
