/*
ID: wentcui1
LANG: C
TASK: kimbits
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITF 2147483647

main() {
	FILE* fin = fopen("kimbits.in", "r");
	FILE* fout = fopen("kimbits.out", "w");
	int N, L;
	int i, j, k;
	int highest = 0, temphighest;
	unsigned int ret = 0, I;
	fscanf(fin, "%d %d %u\n", &N, &L, &I);
	unsigned int* dp[33];
	unsigned int rec[33];
	for(i = 0; i <= 32; i++) {
		dp[i] = (unsigned int*)malloc(sizeof(unsigned int) * (N + 1));
		memset(dp[i], 0, sizeof(unsigned int) * (N + 1));
	}
	for(i=0; i<=N; i++)
		dp[0][i] = dp[i][0] = 1;
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
		}
	}
	for(i=N; i>=1; i--) {
        if(I>dp[i-1][L]){
			fprintf(fout, "1");
            I -= dp[i-1][L];
            --L;
        }else
			fprintf(fout, "0");
	}
	fprintf(fout, "\n");
	exit(0);
}
