#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int base, len;
char input[20];
unsigned long dp[20][(1 << 16) + 1] = {{0}};

int getnextmod(int cur, int mod, int curindex) {
	int shift = len - curindex, i, res = cur % mod;
	for(i = 1; i <= shift; i++) {
		res = (res * base) % mod;
	}
	return mod - res;
}

unsigned long dfs(unsigned int stat, int mod, int curindex) {
	unsigned mask = (1 << len) - 1;
	unsigned int init = (1 << (len - 1)), i, flipstat = (~stat) & mask;
	unsigned long sum = 0;

	printf("*%d %d\n", mod, flipstat);
	if (dp[mod][flipstat] > 0)
		return dp[flipstat][mod];

	if (curindex == len) {
		for(i = 1; i <= len && !(flipstat & init); i++)
			init = (init >> 1);

		printf("c: %d, i: %d\n", input[i - 1], i - 1);
		if (!(input[i - 1] % mod)) {
			dp[mod][flipstat] = 1;
			return 1;
		}
		return 0;
	}

	for(i = 1; i <= len; i++) {
		if (flipstat & init)
			sum += dfs(stat | init, getnextmod(input[i - 1], mod, curindex), curindex + 1);
		init = (init >> 1);
	}
	dp[mod][flipstat] = sum;
	printf("%d %d: %lu\n", mod, flipstat, sum);
	return sum;
}

int main() {
	int cases, caseno = 0, K, i;
	scanf("%d", &cases);
	while(cases--) {
		for(i = 0; i < 20; i++)
			memset(dp[i], 0, sizeof(unsigned long) * ((1 << 16) + 1));
		memset(input, '\0', sizeof(char) * 20);

		scanf("%d %d", &base, &K);
		scanf("%s", input);
		len = strlen(input);
		for(i = 0; input[i]; i++) {
			if ('A' <= input[i] && input[i] <= 'Z')
				input[i] -= 'A';
			else
				input[i] -= '0';
		}
		printf("Case %d: %lu\n", ++caseno, dfs(0, K, 1));
	}
	return 0;
}
