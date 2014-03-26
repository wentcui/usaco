#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_V -1000000000
#define MAX_V 1000000000

int main() {
	int cases, caseno = 0, N, input[101], dp[101][101];
	int i, j, k, l, e;
	int sum = 0, max, min, runningsum;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &N);
		sum = 0;
		memset(input, 0, sizeof(int) * 101);
		memset(dp, 0, sizeof(int) * 101);

		for(i = 1; i <= N; i++) {
			scanf("%d", &input[i]);
			dp[i][i] = input[i];
			sum += input[i];
		}
		for(k = 2; k <= N; k++) {
			for(i = 1; i <= N - k + 1; i++) {
				e = i + k - 1;
				max = MIN_V;
				runningsum = 0;
				for(j = i; j <= e; j++) {
					runningsum += input[j];
					if (j == e) {
						if (runningsum > max)
							max = runningsum;
						break;
					}
					min = MAX_V;
					if (j + 1 == e)
						min = 0;
					for(l = j + 1; l <= e; l++) {
						if (l < e && dp[j + 1][l] < min)
							min = dp[j + 1][l];
						if (l > j + 1 && dp[l][e] < min)
							min = dp[l][e];
					}
					if (runningsum + min > max)
						max = runningsum + min;
					//printf("max: %d, min: %d\n", max, min);
				}

				runningsum = 0;
				for(j = e; j >= i; j--) {
					runningsum += input[j];
					if (j == i) {
						if (runningsum > max)
							max = runningsum;
						break;
					}
					min = MAX_V;
					if (j - 1 == i)
						min = 0;
					for(l = j - 1; l >= i; l--) {
						if (l < j - 1 && dp[i][l] < min)
							min = dp[i][l];
						if (l > i && dp[l][j - 1] < min)
							min = dp[l][j - 1];
					}
					if (runningsum + min > max)
						max = runningsum + min;
					//printf("*max: %d, min: %d, j: %d, i: %d\n", max, min, j, i);
				}
				//printf("i: %d, e: %d, v: %d\n", i, e, max);
				dp[i][e] = max;
			}
		}
		printf("Case %d: %d\n", ++caseno, 2 * dp[1][N] - sum);
	}
	return 0;
}
