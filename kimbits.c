/*
ID: wentcui1
LANG: C
TASK: kimbits
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


main() {
	FILE* fin = fopen("kimbits.in", "r");
	FILE* fout = fopen("kimbits.out", "w");
	int N, L, I;
	int i, j, k;
	int highest = 0, temphighest;
	unsigned int ret = 0;
	fscanf(fin, "%d %d %d\n", &N, &L, &I);
	int* dp[32];
	int rec[32];
	for(i = 0; i <= 31; i++) {
		dp[i] = (int*)malloc(sizeof(int) * (L + 1));
		memset(dp[i], 0, sizeof(int) * (L + 1));
	}

	dp[1][1] = 1;
	for(i = 1; i <= 31; i++) {
		dp[i][0] = 1;
		rec[i] = 1;
	}
	rec[1] = 2;
	for(i = 2; i <= 31; i++) {
		for(j = 1; j <= i && j <= L; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
			rec[i] += dp[i][j];
		}
		if (rec[i] > I) {
			highest = i;
			break;
		}
	}

	temphighest = highest;
	while(I && L) {
		while(rec[highest] > I)
			highest--;
		if(rec[highest] == I) {
			while(highest && L) {
				ret |= (1 << (highest - 1));
				L--;
				highest--;
			}
			break;
		} else {
			ret |= (1 << highest);
			I -= rec[highest];
			L--;
		}
	}
	printf("%d, %d\n", ret, temphighest);
	while(temphighest > 0) {
		fprintf(fout, "%d", (ret & (1 << (temphighest - 1))) > 0);
		temphighest--;
	}
	fprintf(fout, "\n");
	exit(0);
}
