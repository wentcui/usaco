/*
ID: wentcui1
LANG: C++
TASK: fence8
*/

#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
	printf("\nfsdfd\n");
	FILE* fin = fopen("fence8.in", "r");
	FILE* fout = fopen("fence8.out", "w");
	int i, j, k;
	int boards[51] = {0};
	int rails[1024] = {0};
	printf("fsdfd\n");
	int dp[128][51][129] = {{{0}}};
	int N, R;

	printf("fsdfd\n");
	fscanf(fin, "%d", &N);
	for(i = 1; i <= N; i++)
		fscanf(fin, "%d", &boards[i]);
	fscanf(fin, "%d", &R);
	for(i = 1; i <= R; i++)
		fscanf(fin, "%d", &rails[i]);
	printf("fsdfd2\n");

	for(i = 1; i <= R; i++) {
		for(j = 1; j <= N; j++) {
			for(k = 1; k <= boards[j]; k++) {
				if (k < rails[i]) {
					dp[i][j][k] = max(dp[i - 1][j][k], dp[i][j - 1][boards[j - 1]]);
				} else {
					dp[i][j][k] = max(dp[i - 1][j][k], max(dp[i - 1][j][k - rails[i]], dp[i - 1][j - 1][boards[j - 1]]) + 1);
				}
				
			}
		}
	}

	printf("%d\n\n", dp[R][N][boards[N]]);
	return 0;
}
