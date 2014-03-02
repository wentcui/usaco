#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int64 long long
char s1[35],s2[35];
int64 dp[35][35][75];

int main() {
	int cases, caseno = 0;
	int i, j, k, l1, l2;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%s%s", s1 + 1, s2 + 1);
		l1 = strlen(s1 + 1);
		l2 = strlen(s2 + 1);
		dp[0][0][0] = 1;
		for(i = 1; i <= l1; i++)
			dp[i][0][i] = 1;
		for(i = 1; i <= l2; i++)
			dp[0][i][i] = 1;
		for(k = 1; k <= l1 + l2; k++)
			for(i = 1; i <= l1; i++)
				for(j = 1; j <= l2; j++) {
					if (i + j < k)	continue;
					if (s1[i] == s2[j])
						dp[i][j][k] = dp[i - 1][j - 1][k - 1];
					else
						dp[i][j][k] = dp[i - 1][j][k - 1] + dp[i][j - 1][k - 1];
				}

		for(k = 1; k <= l1 + l2; k++) {
			if (dp[l1][l2][k] > 0) {
				printf("Case %d: %d %llu\n", ++caseno, k, dp[l1][l2][k]);
				break;
			}
		}
	}
	return 0;
}
