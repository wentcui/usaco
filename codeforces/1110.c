#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
	return a > b ? a : b;
}
void reverse(char *str) {
	int end = strlen(str) - 1;
	int start = 0;
	printf("end: %d\n", end);
	while(start < end) {
		char c = str[start];
		str[start] = str[end];
		str[end] = c;
		start++, end--;
	}
}

void fn(char *inputa, char *inputb, char *res) {
	int dp[102][102] = {{0}};
	int i, j, index = 0, count, end;
	int lena = strlen(inputa), lenb = strlen(inputb);
	char min_c = 'z', min_id;
	printf("ia: %s, ib: %s\n", inputa, inputb);
	for(i = 1; i <= lena; i++) {
		for(j = 1; j <= lenb; j++) {
			if (inputa[i - 1] == inputb[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
		}
	}

	count = dp[lena][lenb];
	printf("count: %d\n", count);
	end = lenb;
	for(i = lena; i > 0 && count; i--) {
		min_c = 'z';
		for(j = end; j > 0; j--) {
			if (dp[i][j] == count) {
				if (inputb[j - 1] <= min_c) {
					min_c = inputb[j - 1];
					min_id = j;
				}
			}
		}
		printf("id: %d, c: %c\n", min_id, min_c);
		count--;
		res[index++] = min_c;
		end = min_id - 1;
	}
}

int main() {
	int cases, caseno = 0;
	char inputa[102], inputb[102], res[102];
	scanf("%d", &cases);
	while(cases--) {
		memset(inputa, 0, sizeof(inputa));
		memset(inputb, 0, sizeof(inputb));
		memset(res, 0, sizeof(res));

		scanf("%s%s", inputa, inputb);
		printf("ia: %s, ib: %s\n", inputa, inputb);
		reverse(inputa);
		reverse(inputb);
		fn(inputa, inputb, res);
		if (strlen(res))
			printf("Case %d: %s\n", ++caseno, res);
		else
			printf("Case %d: :(\n", ++caseno);
	}
}
