#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int base, len, K;
char input[21];
unsigned long dp[21][(1 << 16) + 1] = {{0}};
bool map[21][(1 << 16) + 1] = {{false}};

int getnextmod(int cur, int mod, int curindex) {
	int shift = len - curindex, i, res = cur % K;
	for(i = 1; i <= shift; i++) {
		res = (res * base) % K;
	}
	return mod - res >= 0 ? mod - res : mod - res + K;
}

unsigned long dfs(unsigned int stat, int mod, int curindex) {
	unsigned mask = (1 << len) - 1;
	unsigned int init = (1 << (len - 1)), i, flipstat = (~stat) & mask;
	unsigned long sum = 0, temp;

//	printf("*%d %d, %d\n", mod, flipstat, curindex);
	if (map[mod][flipstat])
		return dp[mod][flipstat];

	if (curindex == len) {
		for(i = 1; i <= len && !(flipstat & init); i++)
			init = (init >> 1);

		map[mod][flipstat] = true;
		if ((input[i - 1] % K) == (mod % K)) {
			//printf("yes\n");
			dp[mod][flipstat] = 1;
			return 1;
		}
	//	printf("no\n");
		return 0;
	}

	for(i = 1; i <= len; i++) {
		if (flipstat & init) {
			temp = dfs(stat | init, getnextmod(input[i - 1], mod, curindex), curindex + 1);
			sum += temp;
			//printf("ret: %lu, stat: %d, mod: %d\n", temp, stat | init, getnextmod(input[i - 1], mod, curindex));
		}
		init = (init >> 1);
	}
	dp[mod][flipstat] = sum;
	map[mod][flipstat] = true;
	//printf("%d %d: %lu\n", mod, flipstat, sum);
	return sum;
}

int main() {
	int cases, caseno = 0, i;
	scanf("%d", &cases);
	while(cases--) {
		for(i = 0; i < 21; i++) {
			memset(dp[i], 0, sizeof(unsigned long) * ((1 << 16) + 1));
			memset(map[i], false, sizeof(bool) * ((1 << 16) + 1));
		}
		memset(input, '\0', sizeof(char) * 20);

		scanf("%d %d", &base, &K);
		scanf("%s", input);
		len = strlen(input);
		for(i = 0; input[i]; i++) {
			if ('A' <= input[i] && input[i] <= 'Z')
				input[i] -= ('A' - 10);
			else
				input[i] -= '0';
		}
		printf("Case %d: %lu\n", ++caseno, dfs(0, K, 1));
	}
	return 0;
}
