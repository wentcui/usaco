#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned long fn(char *str) {
	int len = strlen(str + 1), i, j, k;
	unsigned long sum, dp[61][61] = {{0}};
	for(i = 1; i <= len; i++)
		dp[i][i] = 1;

	for(i = 2; i <= len; i++) {
		for(j = 1; j <= len - i + 1; j++) {
			sum = dp[j][j + i - 2];
			for(k = j; k < j + i - 1; k++) {
				if (str[k] != str[j + i - 1])	continue;
				else if (k + 1 <= j + i - 2) {
					sum += (dp[k + 1][j + i - 2] + 1);
				} else {
					sum += 1;
				}
			}
			dp[j][j + i - 1] = sum + 1;
		}
	}
	return dp[1][len];
}

int main() {
	int cases, caseno = 0;
	char input[61];
	scanf("%d", &cases);
	while(cases--) {
		memset(input, '\0', sizeof(char) * 61);
		scanf("%s", input + 1);
		printf("Case %d: %lu\n", ++caseno, fn(input));
	}
	return 0;
}
