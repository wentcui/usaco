#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 100000000

using namespace std;

int N, R, S, T;
int dp[101][101];

int min(int a, int b) {
	return a < b ? a : b;
}

int floyd(void) {
	int i, j, k;
	int max = 0;
	for(k = 1; k <= N; k++) {
		for(i = 1; i <= N; i++) {
			for(j = 1; j <= N; j++) {
				dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);
			}
		}
	}
	max = dp[S][T];
	for(i = 1; i <= N; i++) {
		if (dp[S][i] + dp[i][T] > max)
			max = dp[S][i] + dp[i][T];
	}
	return max;
}

int main() {
	int cases, caseno = 0, s, t;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &N);
		scanf("%d", &R);
		for(int i = 0; i <= 100; i++)
			for(int j = 0; j <= 100; j++)
				dp[i][j] = INF;
		for(int i = 1; i <= N; i++)
			dp[i][i] = 0;

		for(int i = 1; i <= R; i++) {
			scanf("%d %d", &s, &t);
			dp[s + 1][t + 1] = 1;
			dp[t + 1][s + 1] = 1;
		}
		scanf("%d %d", &S, &T);
		S++, T++;
		printf("Case %d: %d\n", ++caseno, floyd());
	}
	return 0;
}

