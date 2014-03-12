#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned long fn(char *str) {
	int len = strlen(str), dp[61][61] = {{0}}, i, j, k;
	unsigned long sum;
	for(i = 1; i <= len; i++)
		dp[i][i] = 1;

	for(i = 2; i <= len; i++) {
		for(j = 1; j <= len - i + 1; j++) {
			sum = dp[j][j + i - 2];
			for(k = j; k < j + i - 1; k++) {
				if (str[k - 1] != str[j + i - 2])	continue;
				else if (k + 1 <= j + i - 2)
					sum += dp[k + 1][j + i - 2];
				else
					sum += 1;
			}
			dp[j][j + i - 1] = sum + len;
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
		scanf("%s", input);
		printf("Case %d: %lu", ++caseno, fn(input));
	}
	return 0;
}
