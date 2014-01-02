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
	int values[51];
	memset(values, 0, (sizeof(int) * 51));
	for(i = 1; i <= N; i++) {
		fscanf(fin, "%d", &values[i]);
		if (max < values[i])
			max = values[i];
	}
	int* dp = (int *)malloc(sizeof(int) * (max * K + 1));
    memset(dp, 0, sizeof(int) * (max * K + 1));
    dp[0] = 1;
	values[0] = 1;
    for(i = 1; i <= K; i++) {
        for(j = i * max; j > 0; j--) {
        	int v = 0;
            for(k = N; k >= 0; k--) {
                if (j >= values[k])
                    v |= dp[j - values[k]];
				if (v) break;
			}
			dp[j] = v;
		}
	}

	for(i = 1; i <= K * max; i++) {
		if (!dp[i])
			break;
	}
	fprintf(fout, "%d\n", i - 1);
	exit(0);
}
