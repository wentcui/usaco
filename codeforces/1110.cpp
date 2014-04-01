#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}
void reverse(char *str) {
	int end = strlen(str) - 1;
	int start = 0;
	while(start < end) {
		char c = str[start];
		str[start] = str[end];
		str[end] = c;
		start++, end--;
	}
}

char search(char *inputa, char *inputb, int dp[102][102], int &mrow, int &mcol, int count) {
	int i, j;
	int min_i, min_j, min_c = 'z' + 1;
	for(i = mrow; i >= count; i--) {
		for(j = mcol; j >= count; j--) {
			if (dp[i][j] == count && inputa[i - 1] == inputb[j - 1]) {
				if (inputa[i - 1] < min_c) {
					min_c = inputa[i - 1];
					min_i = i;
					min_j = j;
				}
			}
		}
	}
	mrow = min_i - 1;
	mcol = min_j - 1;
	return inputa[min_i - 1];
}

void fn(char *inputa, char *inputb, char *res) {
	int dp[102][102] = {{0}};
	int i, j, index = 0, count, mrow, mcol;
	int lena = strlen(inputa), lenb = strlen(inputb);
	for(i = 1; i <= lena; i++) {
		for(j = 1; j <= lenb; j++) {
			if (inputa[i - 1] == inputb[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
		}
	}

	count = dp[lena][lenb];
	mrow = lena;
	mcol = lenb;
	while(count) {
		res[index++] = search(inputa, inputb, dp, mrow, mcol, count);
		count--;
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
		reverse(inputa);
		reverse(inputb);
		fn(inputa, inputb, res);
		if (strlen(res))
			printf("Case %d: %s\n", ++caseno, res);
		else
			printf("Case %d: :(\n", ++caseno);
	}
}
