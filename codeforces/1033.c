#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 2000000000

int min(int a, int b) {
	return a < b ? a : b;
}

int fn(char *rec) {
	char dp[101][101] = {{0}};
	int len = strlen(rec);
	for(int k = 2; k <= len; k++) {
		for(int i = 1; i <= len - k + 1; i++) {
			int j = i + k - 1;
			dp[i][j] = min(dp[i][j - 1], dp[i + 1][j]) + 1;
			if (rec[i - 1] == rec[j - 1])
				dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
		}
	}
	return (int)dp[1][len];
}

int main() {
	int cases, caseno = 0, len;
	char input[102];
	scanf("%d", &cases);
	while(cases--) {
		memset(input, '\0', sizeof(char) * 102);
		scanf("%s", input);
		printf("Case %d: %d\n", ++caseno, fn(input));
	}
	return 0;
}
