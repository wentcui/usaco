/*
ID: wentcui1
LANG: C
TASK: stamps
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main() {
	FILE* fin = fopen("stamps.in", "r");
	FILE* fout = fopen("stamps.out", "w");

	int K, N, i, j, k, l, max = 0;
	fscanf(fin, "%d %d", &K, &N);
	int values[10001];
	memset(values, 0, sizeof(int) * (10001));
	int** dp = (int **)malloc(sizeof(int *) * (K + 1));
	for(i = 1; i <= N; i++) {
		fscanf(fin, "%d", &values[i]);
		if (max < values[i])
			max = values[i];
	}
	for(i = 0; i <= K; i++) {
		dp[i] = malloc(sizeof(int) * (max * K + 1));
		memset(dp[i], 0, sizeof(int) * (max * K + 1));
	}
	printf("s\n");

	for(i = 1; i <= K; i++) {
		dp[i][0] = 1;
	}
	for(i = 1; i <= N; i++) {
		dp[1][values[i]] = 1;
	}
	printf("s1\n");

	for(i = 1; i <= N; i++) {
		for(j = 2; j <= K; j++) {
			for(k = 1; k <= max * K; k++) {
				int v = 0;
				for(l = 0; l <= j && k - l * values[i] >= 0; l++) {
					v |= dp[j - l][k - l * values[i]];
				}
				dp[j][k] = v;
			}
		}
	}

	for(k = 1; k <= max * K; k++) {
		for(i = 1; i <= K; i++) {
			if (dp[i][k])
				break;
		}
		if (i > K)
			break;
	}

	printf("Final: %d\n", k - 1);
	exit(0);
}
