/*
ID: wentcui1
LANG: C
TASK: money
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main()
{
	int v, n;
	int i, j, k;
	FILE* fin = fopen("money.in", "r");
	FILE* fout = fopen("money.out", "w");
	fscanf(fin, "%d %d", &v, &n);
	fgetc(fin);
	int *arr = (int *)malloc(sizeof(int) * v);
	for(i = 0; i < v; i++) {
		fscanf(fin, "%d", &arr[i]);
		if (i < v - 1)
			fgetc(fin);
	}
	unsigned long long int **dp = (unsigned long long int **)malloc(sizeof(unsigned long long int *) * (v + 1));
	for(i = 0; i <= v; i++) {
		dp[i] = (unsigned long long int *)malloc(sizeof(unsigned long long int) * (n + 1));
		memset(dp[i], 0, sizeof(unsigned long long int) * (n + 1));
	}
	for(i = 0; i <= v; i++) {
		dp[i][0] = 1;
	}
	
	for(i = 1; i <= v; i++) {
		for(j = 1; j <= n; j++) {
			unsigned long long int sum = 0;
			for(k = 0; k * arr[i - 1] <= j; k++) {
				sum += dp[i - 1][j - k * arr[i - 1]];
			}
			dp[i][j] = sum;
		}
	}
	fprintf(fout, "%llu\n", dp[v][n]);
	fclose(fout);
	exit(0);
}
