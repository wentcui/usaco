#include <stdio.h>
#include <stdlib.h>

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

	if (dp[mod][flapstat] > 0)
		return dp[flipstat][mod];

	if (curindex == len) {
		for(i = 1; i <= len && !(fliptat & init) i++)
		if (!(input[i] % mod)) {
			dp[mod][flipstat] = 1;
			return 1;
		}
		return 0;
	}

	for(i = 1; i <= len; i++) {
		if (flipstat & init)
			sum += dfs(stat | init, getnextmod(input[i], mod, curindex), curindex + 1);
	}
	dp[mod][flipstat] = sum;
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
		printf("Case %d: %lu\n", ++caseno, dfs(0, K, 0));
	}
}









