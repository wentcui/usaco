#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fun(char *str1, char *str2, char *str3) {
	vector<int> cmap1[32], cmap2[32];
	int dp[101][101][101] = {{{0}}};
	int pos, sum, p, len1 = strlen(str1), len2 = strlen(str2), len3 = strlen(str3);
	int lastv;
	if (len1 + len2 < len3)
		return 0;
	for(int i = 0; i < len1; i++)
		cmap1[str1[i] - 'a'].add(i + 1);
	for(int i = 0; i < len2; i++)
		cmap2[str2[i] - 'a'].add(i + 1);

	for(int i = 1; i <= len1; i++)
	for(int j = 1; j <= len2; j++)
	for(int k = 1; k <= len3; k++) {
		if (i + j < k)	continue;
		sum = 0;
		lastv = str3[k - 1] - 'a';
		for(int l = 0; l < cmap1[lastv].size(); l++) {
			p = cmap1[lastv][l];
			if (p > i)	break;
			sum = (sum + dp[p - 1][j][k - 1]) % 1000000007;
		}

		for(int l = 0; l < cmap2[lastv].size(); l++) {
			p = cmap2[lastv][l];
			if (p > i)	break;
			sum = (sum + dp[i][p - 1][k - 1]) % 1000000007;
		}
		dp[i][j][k] = sum % 1000000007;
	}
	return dp[len1][len2][len3];
}

int main() {
	int cases, caseno = 0;
	char str1[101], str2[101], str3[101];
	scanf("%d", &cases);
	while(cases--) {
		memset(str1, 0, sizeof(str1));
		memset(str2, 0, sizeof(str1));
		memset(str3, 0, sizeof(str1));
		scanf("%s %s %s", str1, str2, str3);
		printf("Case %d: %d\n", ++caseno, fun(str1, str2, str3));
	}
	return 0;
}
