/*
ID: wentcui1
LANG: C++
TASK: shopping
*/

#include <stdio.h>
#include <stdlib.h>

#define ITF 200000000
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

int get_oldstate(int *offer, int *idx, int state, int *map) {
	int i, n, pos;
	n = offer[0];
	for(i = 1; i <= n; i++) {
		pos = map[offer[2 * i]];
		if (idx[pos] < offer[2 * i + 1])
			return -1;
		state -= (base(5 - pos) * offer[2 * i + 1]);
	}
	return state;
}

main() {
	int offers[100][12] = {{0}};
	int products[6][3] = {{0}};
	int dp[66666] = {ITF};
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
		//printf("%d %d %d\n", products[i][0], products[i][1], products[i][2]);
		map[products[i][0]] = i;
	}

	dp[0] = 0;
	for(idx[1] = 0; idx[1] <= products[1][1]; idx[1]++)
	for(idx[2] = 0; idx[2] <= products[2][1]; idx[2]++)
	for(idx[3] = 0; idx[3] <= products[3][1]; idx[3]++)
	for(idx[4] = 0; idx[4] <= products[4][1]; idx[4]++)
	for(idx[5] = 0; idx[5] <= products[5][1]; idx[5]++) {
		state = idx[1] * 10000 + idx[2] * 1000 + idx[3] * 100 + idx[4] * 10 + idx[5] * 1;
		//printf("state: %d\n", state);
		int runningmin = ITF;
		for(i = 0; i < s; i++) {
			old_state = get_oldstate(offers[i], idx, state, map);
			if (old_state < 0)	continue;
			//printf("old_state: %d, offer[%d][1]: %d\n", old_state, i, offers[i][1]);
			if (dp[old_state] + offers[i][1] < runningmin)
				runningmin = dp[old_state] + offers[i][1];
		}
		for(j = 5; j > 0; j--) {
			if (idx[j] > 0)
				break;
		}
		if (j == 0)
			continue;

		//printf("runningmin: %d\n", runningmin);
		old_state = state - base(5 - j);
		dp[state] = min(dp[old_state] + products[j][2], runningmin);
		//printf("old_state: %d, product[%d][2]: %d, dp[%d]: %d\n", old_state, j, products[j][2], state, dp[state]);
	}

	state = products[1][1] * 10000 + products[2][1] * 1000 + products[3][1] * 100 + products[4][1] * 10 + products[5][1] * 1;
	fprintf(fout, "%d\n", dp[state]);
	fclose(fout);
	fclose(fin);

	exit(0);
}
