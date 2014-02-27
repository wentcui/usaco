#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V (1 << 30) - 1

int rec[1024];
int dp[1024][1024];
int n, k;

int max(int a, int b) {
	return a > b ? a : b;
}

int fn(int *arr, int ln, int lc) {
	int i, sum = 0, runningmax = 0, min = MAX_V;
	if (!lc)
		return 0;
	if (dp[ln][lc])
		return dp[ln][lc];

	if (!ln) {
		for(i = 0; i < lc; i++) 
			sum += arr[i];
		dp[ln][lc] = sum;
		return sum;
	}
	for(i = 0; i < lc && i <= lc - ln; i++) {
		sum += arr[i];
		runningmax = max(sum, fn(arr + i + 1, ln - 1, lc - i - 1));
		if (runningmax < min)
			min = runningmax;
	}
	dp[ln][lc] = min;
	return min;
}

int main() {
	int cases, caseno = 0;
	int i,j;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &k);
		for(i = 1; i <= n + 1; i++) {
			scanf("%d", &rec[i]);
		}
		for(i = 0; i <= n + 1; i++)
			memset(dp[i], 0, sizeof(int) * 1024);
		printf("Case %d: %d\n", ++caseno, fn(rec + 1, k, n + 1));
	}
	return 0;
}
