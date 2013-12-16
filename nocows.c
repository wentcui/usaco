/*
ID: wentcui1
LANG: C
TASK: nocows
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node {
	int nr;
	int heights[102];
};

int max(int a, int b) 
{
	return (a > b) ? a :b;
}

main()
{
	struct node **dp;
	int n, hi, nr = 0;
	int i, j, x, y;
	FILE *fin = fopen("nocows.in", "r");
	FILE *fout = fopen("nocows.out", "w");

	fscanf(fin, "%d %d", &n, &hi);
	if (n % 2 == 0) {
		fprintf(fout, "0\n");
		exit(0);
	}

	dp = (struct node **)malloc(sizeof(struct node *) * (n + 1));
	dp[0] = (struct node *)malloc(sizeof(struct node));
	dp[0]->nr = 0;
	memset(dp[0]->heights, 0, sizeof(int) * 102);

	dp[1] = (struct node *)malloc(sizeof(struct node));
	dp[1]->nr = 1;
	memset(dp[0]->heights, 0, sizeof(int) * 102);
	dp[1]->heights[1] = 1;

	for(i = 3; i <= n; i++) {
		if (!(i % 2)) continue;
		int cur_nr = 0;
		dp[i] = (struct node *)malloc(sizeof(struct node));
		memset(dp[i]->heights, 0, sizeof(int) * 102);

		for(j = 2; j < i; j++) {
			if (j % 2) continue;
			
			int *prev_heights = dp[j - 1]->heights;
			int *last_heights = dp[i - j]->heights;
			for(x = 1; x < hi; x++) {
				if (prev_heights[x] == 0) continue; 
				for(y = 1; y < hi; y++) {
					if (last_heights[y] == 0) continue; 

					dp[i]->heights[max(x, y) + 1] = (dp[i]->heights[max(x, y) + 1] + prev_heights[x] * last_heights[y]) % 9901;
				}
			}
		}
	}
	fprintf(fout, "%d\n", dp[n]->heights[hi]);
	fclose(fout);
	exit(0);
}
