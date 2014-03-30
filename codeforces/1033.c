#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 2000000000

int fn(char *rec) {
	int dp[204][204] = {{0}};
	int len = strlen(rec), mid, left, min = MAX_V;
	for(int i = 2; i <= len; i++) {
		for(int j = 1; j <= i; j++) {
			mid = i / 2;
			dp[i][j] = dp[i - 1][j] + 1
			if (j <= mid)	continue;

			left = 2 * j - i;
			if (rec[left - 1] == rec[i - 1])
				dp[i][j] -= 2;
		}
	}
	for(int i = 1; i <= len; i++) {
		if (dp[N][i] < min)
			min = dp[N][i];
	}
	return min;
}

int main() {
	int cases, caseno = 0, len;
	char input[101], rec[204]
	scanf("%d", &cases);
	while(cases--) {
		memset(input, '\0', sizeof(char) * 101);
		memset(rec, '\0', sizeof(char) * 204);
		scanf("%s", input);
		len = strlen(input);
		for(int i = 0; i < len; i++) {
			rec[2 * i] = '#';
			rec[2 * i + 1] = input[i];
		}
		printf("Case %d: %d\n", ++caseno, fn(rec));
	}
	return 0;
}
