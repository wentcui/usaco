#include <stdio.h>
#include <stdlib.h>

int N, W, K;

int max(int a, int b) {
	return a > b ? a : b;
}

int bSearch(int *arr, int start, int end, int value) {
	int mid, l = start, r = end;
	while(l < r) {
		mid = l + (r - l) / 2;
		if (arr[mid] < value)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}

int fun(int *input, int *input_count) {
	int dp[101][101], accu_count[101];
	int i, j, k, start, last;
	accu_count[1] = inout_count[1];
	for(i = 2; i <= N; i++)
		accu_count[i] = accu_count[i - 1] + input_count[i];
	
	for(k = 1; k <= K; k++) {
		start = last = 1;
		for(i = 1; i <= N; i++) {
			last = start;
			start = bSearch(input, start, i, );
		}
	}
}

int main() {
	int cases, caseno = 0;
	int i, j, k;
	scanf("%d", &cases);
	while (cases--) {
	}
}
