/*
ID: wentcui1
LANG: C
TASK: inflate
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long max(unsigned long a, unsigned long b) {
	return a > b ? a : b;
}

main() {
	FILE* fin = fopen("inflate.in", "r");;
	FILE* fout = fopen("inflate.out", "w");;
	int i, j;
	int M[10001], P[10001];
	int pos = 0;
	unsigned long dp[10001];
	memset(dp, 0, sizeof(unsigned long) * 10001);

	int m, n;
	fscanf(fin, "%d %d", &m, &n);
	for(i = 0; i < n; i++) {
		pos++;
		fscanf(fin, "%d %d", &P[pos], &M[pos]);
	}

	for(i = 1; i <= m; i++) {
		unsigned long runningmax = 0;
		for(j = 1; j <= n; j++) {
			int index = i - M[j];
			if (index >= 0)
				runningmax = max(runningmax, dp[index] + P[j]);
		}
		dp[i] = runningmax;
	}

	fprintf(fout, "%lu\n", dp[m]);
	fclose(fout);
	exit(0);
}
