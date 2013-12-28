/*
ID: wentcui1
LANG: C
TASK: fact4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getFirst(int v) {
	while(!(v % 10))
		v /= 10;
	return (v % 10);
}

main() {
	FILE* fin = fopen("fact4.in", "r");
	FILE* fout = fopen("fact4.out", "w");

	int n, i;
	fscanf(fin, "%d", &n);
	int* dp = (int *)malloc(sizeof(int) * (n + 1));
	memset(dp, 0, sizeof(int) * (n + 1));

	dp[1] = 1;
	for(i = 2; i <= n; i++) {
		dp[i] = getFirst(dp[i - 1] * i);
	}

	fprintf(fout, "%d\n", dp[n]);
	fclose(fin);
	fclose(fout);

	exit(0);
}
