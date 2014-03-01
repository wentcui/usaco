#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N, W, K;

int max(int a, int b) {
	return a > b ? a : b;
}

int cmp(const void *a,const void *b) {
	int *x = (int *) a;
	int *y = (int *) b;
	return *x - *y;
}

int bSearch(int *arr, int start, int end, int value) {
	int mid, l = start, r = end;
	if (value <= 0)
		return 1;
	while(l < r) {
		mid = l + (r - l) / 2;
		if (arr[mid] < value)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}

int fun(int *input, int *input_count, int len) {
	int dp[101][101], accu_count[101];
	int i, j, k, start, last;
	memset(accu_count, 0, sizeof(int) * 101);
	for(i = 0; i < 101; i++) {
		memset(dp[i], 0, sizeof(int) * 101);
	}
	accu_count[1] = input_count[1];
	for(i = 2; i <= len; i++)
		accu_count[i] = accu_count[i - 1] + input_count[i];

	for(k = 1; k <= K; k++) {
		start = last = 1;
		for(i = 1; i <= len; i++) {
			last = start;
			start = bSearch(input, start, i, input[i] - W);

			dp[i][k] = max(dp[i - 1][k], dp[start - 1][k - 1] + accu_count[i] - accu_count[start - 1]);
		}
	}
	return dp[len][K];
}

int main() {
	int cases, caseno = 0;
	int i, j, last, count, x;
	int raw_input[101], input[101], input_count[101];
	scanf("%d", &cases);
	while (cases--) {
		scanf("%d %d %d", &N, &W, &K);
		memset(input, 0, sizeof(int) * 101);
		memset(input_count, 0, sizeof(int) * 101);

		for(i = 1; i <= N; i++) {
			scanf("%d %d", &x, &raw_input[i]);
		}

		qsort (raw_input, N + 1, sizeof(int), cmp);
		last = raw_input[1];
		count = 1;
		input[1] = last;
		for(i = 2, j = 2; i <= N; i++) {
			if (raw_input[i] != last) {
				input[j] = raw_input[i];
				input_count[j - 1] = count;
				last = raw_input[i];
				count = 1;
				j++;
			} else {
				count++;
			}
		}
		input_count[j - 1] = count;
		printf("Case %d: %d\n", ++caseno, fun(input, input_count, j - 1));
	}
}





