/*
ID: wentcui1
LANG: C
TASK: checker
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count = 0;
int* res[3];
unsigned int mask = 0;

int getpos(unsigned int v) {
	int ret = 0;
	while(v > 0) {
		v = (v >> 1);
		ret++;
	}
	return ret;
}

void dfs(int rowup, int leftup, int rightup, int current)
{
	if (rowup < mask) {
		unsigned int available = (~(rowup | leftup | rightup)) & mask;
		unsigned int f;
		while(available) {
			f = (available & (~(available - 1)));
			if (count < 3) {
				res[count][current] = getpos(f);
			}
			dfs(rowup | f, (leftup | f) >> 1, (rightup | f) << 1, current + 1);
			available -= f;
		}
	} else
		count++;
}

main()
{
	int i, j, n;
	FILE *fin = fopen("checker.in", "r");
	FILE *fout = fopen("checker.out", "w");
	
	fscanf(fin, "%d", &n);
	res[0] = (int *)malloc(sizeof(int) * n);
	res[1] = (int *)malloc(sizeof(int) * n);
	res[2] = (int *)malloc(sizeof(int) * n);
	mask = (1 << n) - 1;
	dfs(0, 0, 0, 0);
	for(i = 0; i < 3; i++) {
		for(j = 0; j < n - 1; j++) {
			if (res[i][j] == 0)
				res[i][j] = res[i - 1][j];
			fprintf(fout, "%d ", res[i][j]);
		}
		fprintf(fout, "%d\n", res[i][j]);
	}
	fprintf(fout, "%d\n", count);
	exit(0);
}
