#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fun(char *str) {
	int dp1[51][4] = {{0}}, dp2[51][6] = {{0}};
	int i, j, len = (int)strlen(str);
	int bad, mix, good;
	if ('A' == *str)
		dp1[1][1] = 1;
	else if ('B' == *str)
		dp2[1][1] = 1;
	else
		dp1[1][1] = dp2[1][1] = 1;
	for(i = 2; i <= len; i++) {
		for(j = 0; j <= 2; j++) {
			if (dp1[i - 1][j]) {
				if (str[i - 1] == '?' || str[i - 1] == 'A')	dp1[i][j + 1] = 1;
				if (str[i - 1] == '?' || str[i - 1] == 'B')	dp2[i][1] = 1;
			}
		}
		for(j = 0; j <= 4; j++) {
			if (dp2[i - 1][j]) {
				if (str[i - 1] == '?' || str[i - 1] == 'B')	dp2[i][j + 1] = 1;
				if (str[i - 1] == '?' || str[i - 1] == 'A')	dp1[i][1] = 1;
			}
		}
	}
	bad = mix = good = 0;
	for(i = 0; i <= 2; i++)	if (dp1[len][i])	good = 1;
	for(i = 0; i <= 4; i++)	if (dp2[len][i])	good = 1;
	for(i = 1; i <= len; i++) if (dp1[i][3] || dp2[i][5])	bad = 1;
	if (good && bad)	return 1;
	if (good)	return 0;
	return 2;
}

int main() {
	int i, ret, cases, caseno = 0;
	char input[201];
	scanf("%d", &cases);
	while(cases--) {
		memset(input, 0, sizeof(char) * 201);
		scanf("%s", input);
		for(i = 0; i < strlen(input); i++) {
			if ('?' == input[i])	continue;
			if ('A' == input[i] || 'E' == input[i] || 'O' == input[i]
					|| 'I' == input[i] || 'U' == input[i])
				input[i] = 'A';
			else
				input[i] = 'B';
		}
		ret = fun(input);
		if (!ret)
			printf("Case %d: GOOD\n", ++caseno);
		else if (ret == 1)
			printf("Case %d: MIXED\n", ++caseno);
		else
			printf("Case %d: BAD\n", ++caseno);
	}
	return 0;
}
