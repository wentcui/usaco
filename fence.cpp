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

#define pp pair<int, int>

using namespace std;
int N, finalpos;
int res[501];

int dfs(int s, int pos, int map[][501], vector<int> *graph) {
	int i, ret = 0;
	vector<pp> marked;
	if (pos == N) {
		finalpos = pos;
		return 1;
	}

	for(i = 0; i < graph[s].size(); i++) {
		int d = graph[s][i];
		if (map[s][i]) continue;
		map[s][d] = 1;
		map[d][s] = 1;
		res[pos] = d;
		marked.push_back(make_pair(s, d));

		ret |= dfs(d, pos + 1, map, graph);
		if (ret) return 1;
	}

	for(i = 0; i < marked.size(); i++) {
		map[marked[i].first][marked[i].second] = 0;
	}
	return ret;
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
	}

	for(i = 0; i < 501; i++) {
		if (graph[i].size() > 0)
			break;
	}
	res[0] = i;
	dfs(i, 1, map, graph);

	for(i = 0; i < finalpos; i++) {
		printf("%d", res[i]);
	}

	exit(0);
}
