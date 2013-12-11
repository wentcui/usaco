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
    int s = n * (n + 1) / 2;
    if (s % 2) {
        printf("0\n");
        return;
    }
    int **dp = (int **)malloc(sizeof(int *) * (n + 1));
    for(i = 0; i <= n; i++) {
        dp[i] = (int *)malloc(sizeof(int) * (s + 1));
        memset(dp[i], 0, sizeof(sizeof(int) * (s + 1)));
    }
    for(i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    for(i = 1; i <= n; i++) {
        dp[i][j] = dp[i - 1][j];
        for(j = i; j <= i * (i + 1) / 2 && j <= s; j++) {
            dp[i][j] += dp[i - 1][j - i];
        }
    }
    printf("res: %d\n", dp[n][s / 2]);
}
