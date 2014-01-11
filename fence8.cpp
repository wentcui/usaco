/*
ID: wentcui1
LANG: C++
TASK: fence8
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ITF 2000000000

using namespace std;

int N, R, maxwaste = 0;
int boards[51] = {0};
int rails[1024] = {0};

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

bool dfs(int curr,  int start, int curwaste) {
	int i, waste = curwaste;
	bool ret = false;
	if (curr == 0) {
		return true;
	}

	if (waste > maxwaste) {
		return false;
	}

	for(i = start; i <= N; i++) {
		if (boards[i] >= rails[curr]) {
			boards[i] -= rails[curr];

			if (boards[i] < rails[1]) {
				waste = curwaste + boards[i];
			} else
				waste = curwaste;

			if (rails[curr] == rails[curr - 1])
				start = i;
			else
				start = 1;

			ret |= dfs(curr - 1, start, waste);
			boards[i] += rails[curr];
			if (ret)
				return ret;
		}
	}
	return ret;
}

int main() {
	FILE* fin = fopen("fence8.in", "r");
	FILE* fout = fopen("fence8.out", "w");
	int i, j, k;

	fscanf(fin, "%d", &N);
	for(i = 1; i <= N; i++) {
		fscanf(fin, "%d", &boards[i]);
		maxwaste += boards[i];
	}
	fscanf(fin, "%d", &R);
	for(i = 1; i <= R; i++) {
		fscanf(fin, "%d", &rails[i]);
	}

	qsort(rails, R + 1, sizeof(int), compare);
	qsort(boards, N + 1, sizeof(int), compare);

	for(i = 1; i <= R; i++) {
		maxwaste = maxwaste - rails[i];
		if (!dfs(i, 1, 0))
			break;
	}
	fprintf(fout, "%d\n", i - 1);
	return 0;
}
