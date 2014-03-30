#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 2000000000

int fn(char *rec) {
	int dp[204][204] = {{0}};
	int len = strlen(rec), mid, left, min = MAX_V, min_i;
	int i, j, lc = 0, rc = 0;
	for(i = 2; i <= len; i++) {
		for(j = 1; j < i; j++) {
			mid = i / 2;
			dp[i][j] = dp[i - 1][j] + 1;
			if (j <= mid)	continue;

			left = 2 * j - i;
			if (rec[left - 1] == rec[i - 1])
				dp[i][j] -= 2;
		}
		dp[i][j] = i - 1;
	}
	for(int i = 1; i <= len; i++) {
		if (dp[len][i] < min) {
			min = dp[len][i];
			min_i = i;
		}
	}
	if (min_i != (len + 1) / 2) {
		if (rec[min_i - 1] == '#') {
			lc = (min_i - 1) / 2;
			rc = (len - min_i) / 2;
		} else {
			lc = (min_i - 1) / 2 + 1;
			rc = (len - min_i) / 2 + 1;
		}
	}

	return min - abs(lc - rc);
}

int main() {
	int cases, caseno = 0, len;
	char input[101], rec[204];
	scanf("%d", &cases);
	while(cases--) {
		memset(input, '\0', sizeof(char) * 101);
		memset(rec, '\0', sizeof(char) * 204);
		scanf("%s", input);
		len = strlen(input);
		rec[0] = '#';
		for(int i = 1; i <= len; i++) {
			rec[2 * i - 1] = input[i - 1];
			rec[2 * i] = '#';
		}
		printf("Case %d: %d\n", ++caseno, fn(rec));
	}
	return 0;
}
