/*
ID: wentcui1
TASK: fence6
LANG: C++
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <utility>

#define ITF 200000000
#define PP pair<int, int>

using namespace std;

int minlen = ITF;


struct vertex{
	unsigned int edgesmap[4];
};

void setbit(unsigned int map[4], int pos) {
	int nr = pos / 32;
	int offset = pos % 32;

	map[nr] |= (1 << offset);
}

bool validate(unsigned int m1[4], unsigned int m2[4]) {
	for(int i = 0; i < 4; i++) {
		if (m1[i] != m2[i])
			return false;
	}
	return true;
}

void genMap(unsigned int map[4], vector<int> edges) {
	memset(map, 0, sizeof(unsigned int) * 4);
	for(int i = 0; i < edges.size(); i++) {
		setbit(map, edges[i]);
	}
}

int getVertexId(struct vertex verarr[101], int &vertex_nr, vector<int> edges) {
	unsigned int map[4] = {0};
	genMap(map, edges);
	if (vertex_nr == 1) {
		memset(verarr[1].edgesmap, 0, sizeof(unsigned int) * 4);
		memcpy(verarr[1].edgesmap, map, sizeof(unsigned int) * 4);
		vertex_nr++;
		return 1;
	}

	for(int i = 1; i < vertex_nr; i++) {
		if (validate(verarr[i].edgesmap, map))
			return i;
	}

	memset(verarr[vertex_nr].edgesmap, 0, sizeof(unsigned int) * 4);
	memcpy(verarr[vertex_nr++].edgesmap, map, sizeof(unsigned int) * 4);
	return vertex_nr - 1;

}

void dfs(vector<PP> dist[101], bool map[101], int curlen, int orivertex, int curvertex, int steps) {
	if (curlen > minlen)
		return;
	if (steps <= 2 && curvertex == orivertex)
		return;

	if (curvertex == orivertex) {
		if (curlen < minlen) {
			minlen = curlen;
		}
		return;
	}
	if (curvertex == -1)
		curvertex = orivertex;
	if (map[curvertex])
		return;
	map[curvertex] = true;

	for(int i = 0; i < dist[curvertex].size(); i++) {
		dfs(dist, map, curlen + dist[curvertex][i].second, orivertex, dist[curvertex][i].first, steps + 1);
	}
	map[curvertex] = false;
}

int main() {
	FILE* fin = fopen("fence6.in", "r");
	FILE* fout = fopen("fence6.out", "w");
	struct vertex verarr[101] = {0};
	int i, j, k, e, vertex_nr = 1;
	int N, id, l, n1, n2;
	vector<PP> dist[101];
	bool map[101] = {false};
	int minv = ITF;
	fscanf(fin, "%d", &N);

	for(i = 1; i <= N; i++) {
		int f, t;
		fscanf(fin, "%d %d %d %d", &id, &l, &n1, &n2);
		vector<int> es1, es2;
		es1.push_back(id);
		es2.push_back(id);
		for(j = 1; j <= n1; j++) {
			fscanf(fin, "%d", &e);
			es1.push_back(e);
		}

		for(j = 1; j <= n2; j++) {
			fscanf(fin, "%d", &e);
			es2.push_back(e);
		}

		f = getVertexId(verarr, vertex_nr, es1);
		t = getVertexId(verarr, vertex_nr, es2);
		dist[f].push_back(make_pair(t, l));
		dist[t].push_back(make_pair(f, l));
	}
	for(i = 1; i < vertex_nr; i++) {
		dfs(dist, map, 0, i, -1, 0);
	}
	fprintf(fout, "%d\n", minlen);
	fclose(fout);
	fclose(fin);
	return 0;
}

