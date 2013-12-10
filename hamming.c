/*
ID: wentcui1
LANG: C
TASK: hamming
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int res[64];
int pos = 0;
int N,B,D;
int success = 0;

int countOne(unsigned int v) {
	int ret = 0;
	while (v > 0) {
		ret += (v & 1);
		v = (v >> 1);
	}
	return ret;
}

int gethamdis(unsigned int a, unsigned int b) {
	unsigned int mask = (1 << B) - 1;
	return countOne((a ^ b) & mask);
}

int validate(unsigned int v) {
	int i;
	for(i = 0; i < pos; i++) {
		if (gethamdis(res[i], v) < D)
			return 0;
	}
	return 1;
}

void dfs(unsigned int curv) {
	int max = (1 << B);
	int tempos = pos;
	int i;
	if (success)
		return;
	if (pos == N) {
		success = 1;
		return;
	}
	if (N - pos > max - curv)
		return;
	for(i = curv; i <= max && !success; i++) {
		if (validate(i)) {
			res[pos++] = i;
		}
		dfs(i + 1);
	}
	pos = tempos;
}

main()
{
    int i;
    FILE *fin = fopen("hamming.in", "r");
    FILE *fout = fopen("hamming.out", "w");

    fscanf(fin, "%d %d %d", &N, &B, &D);
	memset(res, 0, sizeof(unsigned int) * 64);
	dfs(0);
	i = 1;
	while (i <= N) {
		fprintf(fout, "%d", res[i - 1]);
		if (i % 10 && i < N)
			fprintf(fout, " ");
		else
			fprintf(fout, "\n");
		i++;	
	}
	fclose(fout);
	return;
}
