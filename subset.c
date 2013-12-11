/*
ID: wentcui1
LANG: C
TASK: subset
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main()
{
    int i, j;
    int n;
    FILE* fin = fopen("subset.in", "r");
    FILE* fout = fopen("subset.out", "w");
    fscanf(fin, "%d", &n);
    long long int s = n * (n + 1) / 2;
    if (s % 2) {
        fprintf(fout, "0\n");
        exit(0);
    }
    long long int **dp = (long long int **)malloc(sizeof(long long int *) * (n + 1));
    for(i = 0; i <= n; i++) {
        dp[i] = (long long int *)malloc(sizeof(long long int) * (s + 1));
        memset(dp[i], 0, sizeof(long long int) * (s + 1));
    }
    for(i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= i * (i + 1) / 2; j++) {
			dp[i][j] += dp[i - 1][j];
			if (j >= i)
            	dp[i][j] += dp[i - 1][j - i];
        }
    }
    fprintf(fout, "%lld\n", dp[n][s / 2] / 2);

	exit(0);
}
