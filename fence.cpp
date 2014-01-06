/*
ID: wentcui1
LANG: C++
TASK: fence
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>

#define pp pair<int, int>

using namespace std;
int N, finalpos = 0;
int res[10024];

void dfs(int s, int pos, int map[][501], vector<int> *graph) {
	int i;
	printf("s: %d\n", s);

	for(i = 501; i >= 1; i--) {
		if (!map[s][i] || !map[i][s]) continue;
		printf("i: %d\n", i);
		map[s][i]--;
		map[i][s]--;

		dfs(i, pos + 1, map, graph);
	}
	printf("get: %d\n", s);
	res[finalpos++] = s;
}

main() {
	FILE *fin = fopen("fence.in", "r");
	FILE *fout = fopen("fence.out", "w");
	int i, j, f, t;
	fscanf(fin, "%d", &N);
	int map[501][501];
	for(i = 0; i <= 500; i++) {
		memset(map[i], 0, sizeof(int) * 501);
	}
	vector<int> graph[501];

	for(i = 0; i < N; i++) {
		fscanf(fin, "%d %d", &f, &t);
		graph[f].push_back(t);
		graph[t].push_back(f);

		map[f][t]++;
		map[t][f]++;
	}


	for(i = 0; i < 501; i++) {
		if (graph[i].size() > 1)
			sort(graph[i].begin(), graph[i].end());
	}

	for(i = 0; i < 501; i++) {
		if (graph[i].size() > 0)
			break;
	}
	printf("size: %lu\n", graph[4].size());
	for(j = i; j < 501; j++) {
		if (graph[j].size() % 2 == 1)
			break;
	}
	printf("j : %d\n\n", j);
	if (j < 501)
		i = j;
	res[0] = i;

	printf("6, 5 %d\n", map[6][5]);
	map[6][5] = 10;

	dfs(i, 1, map, graph);

	for(i = 0; i < finalpos; i++) {
		fprintf(fout, "%d\n", res[i]);
	}

	exit(0);
}
