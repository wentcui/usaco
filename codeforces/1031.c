#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_V -1000000000

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int cases, caseno = 0, N, input, dp[101][101], sum[101];
	int i, j, k, e;
	int max_v;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &N);
		memset(dp, 0, sizeof(int) * 101);
		memset(sum, 0, sizeof(int) * 101);

		for(i = 1; i <= N; i++) {
			scanf("%d", &input);
			dp[i][i] = input;
			sum[i] = sum[i - 1] + input;
		}
		for(k = 2; k <= N; k++) {
			for(i = 1; i <= N - k + 1; i++) {
				e = i + k - 1;
				//max_v = sum[e] - sum[i - 1];
				max_v = MIN_V;
				for(j = i; j <= e; j++) {
					max_v = max(max_v, sum[j] - sum[i - 1] - dp[j + 1][e]);
					max_v = max(max_v, sum[e] - sum[j - 1] - dp[i][j - 1]);
				}
				dp[i][e] = max_v;
			}
		}
		printf("Case %d: %d\n", ++caseno, dp[1][N]);
	}
	return 0;
}
