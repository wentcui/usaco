/*
ID: wentcui1
LANG: C++
TASK: shopping
*/

#include <stdio.h>
#include <stdlib.h>

#define ITF (unsigned int)(-1)
using namespace std;

int min(int a, int b) {
	return a > b ? b : a;
}

// n = 2 return 100, n = 3 return 1000
int base(int n) {
	int i = 1, ret = 1;
	while(i <= n) {
		ret *= 10;
		i++;
	}
	return ret;
}

int get_oldstate(int *offer, int *idx, int *map) {
	int old_state = 0, i, n, pos;
	n = offer[0];
	for(i = 1; i <= n; i++) {
		pos = map[offer[2 * i]];
		if (idx[pos] < offer[2 * i + 1])
			return -1;
		old_state += (base(5 - pos) * (idx[pos] - offer[2 * i + 1]));
	}
	return old_state;
}

main() {
	int offers[100][12] = {{0}};
	int products[6][3] = {{0}};
	int dp[66666] = {0};
	int idx[6] = {0};
	int map[1000] = {0};

	FILE *fin = fopen("shopping.in", "r");
	FILE *fout = fopen("shopping.out", "w");

	int s, b, i, j, n, old_state, state;
	// offers, start from 0
	fscanf(fin, "%d", &s);
	for(i = 0; i < s; i++) {
		fscanf(fin, "%d", &n);
		offers[i][0] = n;
		for(j = 0; j < n; j++) {
			fscanf(fin, "%d %d", &offers[i][2 * j + 2], &offers[i][2 * j + 3]);
		}
		fscanf(fin, "%d", &offers[i][1]);
	}

	// products, start from 1
	fscanf(fin, "%d", &b);
	for(i = 1; i <= b; i++) {
		fscanf(fin, "%d %d %d", &products[i][0], &products[i][1], &products[i][2]);
		map[products[i][0]] = i;
	}

	for(i = 0; i < s; i++) {
		int ori_price = 0;
		for(j = 1; j <= offers[i][0]; j++) {
			ori_price += (products[map[offers[i][2 * j]]][2] * offers[i][2 * j + 1]);
		}
		offers[i][1] = ori_price - offers[i][1];
	}

	for(idx[1] = 0; idx[1] <= products[1][1]; idx[1]++)
	for(idx[2] = 0; idx[2] <= products[2][1]; idx[2]++)
	for(idx[3] = 0; idx[3] <= products[3][1]; idx[3]++)
	for(idx[4] = 0; idx[4] <= products[4][1]; idx[4]++)
	for(idx[5] = 0; idx[5] <= products[5][1]; idx[5]++) {
		state = idx[1] * 10000 + idx[2] * 1000 + idx[3] * 100 + idx[4] * 10 + idx[5] * 1;
		int runningmin = ITF;
		for(i = 0; i < s; i++) {
			old_state = get_oldstate(offers[i], idx, map);
			if (old_state < 0)	continue;
			if (dp[old_state] + offers[i][1] < runningmin)
				runningmin = dp[old_state] + offers[i][1];
		}
		for(j = 5; j > 0; j++) {
			if (idx[j] > 0)
				break;
		}

		old_state = state - base(5 - j);
		dp[state] = min(dp[old_state], runningmin);
	}

	state = products[1][1] * 10000 + products[2][1] * 1000 + products[3][1] * 100 + products[4][1] * 10 + products[5][1] * 1;
	printf("%d", dp[state]);

	exit(0);
}
