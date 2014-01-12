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

#define ITF 200000000

using namespace std;


struct vertex{
	unsigned int edgesmap[3];
};

void setbit(unsigned int map[3], int pos) {
	int nr = pos / 32;
	int offset = pos % 32;

	map[nr] |= (1 << offset);
}

bool validate(unsigned int m1[3], unsigned int m2[3]) {
	for(int i = 0; i < 3; i++) {
		if (m1[i] != m2[i])
			return false;
	}
	return true;
}

void genMap(unsigned int map[3], vector<int> edges) {
	memset(map, 0, sizeof(unsigned int) * 3);
	for(int i = 0; i < edges.size(); i++) {
		setbit(map, edges[i]);
	}
}

int getVertexId(struct vertex verarr[100], int &vertex_nr, vector<int> edges) {
	unsigned int map[3] = {0};
	genMap(map, edges);
	if (vertex_nr == 1) {
		memset(verarr[1].edgesmap, 0, sizeof(unsigned int) * 3);
		memcpy(verarr[1].edgesmap, map, sizeof(unsigned int) * 3);
		vertex_nr++;
		return 1;
	}

	for(int i = 1; i < vertex_nr; i++) {
		if (validate(verarr[i].edgesmap, map))
			return i;
	}

	memset(verarr[vertex_nr].edgesmap, 0, sizeof(unsigned int) * 3);
	memcpy(verarr[vertex_nr++].edgesmap, map, sizeof(unsigned int) * 3);
	return vertex_nr - 1;

}

int main() {
	FILE* fin = fopen("fence6.in", "r");
	FILE* fout = fopen("fence6.out", "w");
	struct vertex verarr[100] = {0};
	int i, j, k, e, vertex_nr = 1;
	int N, id, l, n1, n2;
	int dist[101][101] = {{ITF}};
	for(i = 0; i < 101; i++) {
		for(j = 0; j < 101; j++) {
			dist[i][j] = ITF;
		}
	}
	printf("%d %d\n\n", dist[0][0], dist[0][1]);
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
		dist[f][t] = l;
		dist[t][f] = l;
		printf("%d %d %d\n", id, f, t);
	}


	for(k = 1; k < vertex_nr; k++)
	for(i = 1; i < vertex_nr; i++)
	for(j = 1; j < vertex_nr; j++) {
		dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	}
	for(i = 1; i < vertex_nr; i++) {
		dist[i][i] = ITF;
	}
	for(i = 1; i < vertex_nr; i++) {
		for(j = 1; j < vertex_nr; j++) {
			if (dist[i][j] < ITF)
				printf("dist[%d][%d]: %d\n", i, j, dist[i][j]);
		}
		printf("\n");
	}
	return 0;
}
















