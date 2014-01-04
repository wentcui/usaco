/*
ID: wentcui1
LANG: C
TASK: butter
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITF 200000000

int values[801];

int min(int a, int b) {
	return a > b ? b : a;
}

void swap(int *arr, int a, int b) {
	int t = arr[a];
	arr[a] = arr[b];
	arr[b] = t;
}

void move_up(int *heap, int *values, int id) {
	if (id == 1)
		return;
	int pid = id / 2;
	if (values[heap[pid]] <= values[heap[id]])
		return;
	swap(heap, pid, id);
	move_up(heap, values, pid);
}

void move_down(int *heap, int id) {
	if (values[heap[id]] == ITF)
		return;
	int lc = 2 * id, rc = 2 * id + 1;
	int minid = 0;
	if (min(values[heap[lc]], values[heap[rc]]) >= values[heap[id]])
		return;
	if (values[heap[lc]] <= values[heap[rc]])
		minid = lc;
	else
		minid = rc;

	swap(heap, id, minid);
	move_down(heap, values, minid);
}

void getTop(int *heap, int len, int* ret) {
	ret[0] = heap[1];
	ret[1] = values[heap[1]];
	values[ret] = ITF;
	heap[1] = heap[len - 1];
	heap[len - 1] = 0;
	move_down(heap, values, 1);
}

void addNode(int *heap, int len, int p) {
	heap[len] = p;
	move_up(heap, len);
}

// return the sum of dist when choose p as center
int dij(int p, int **dist, int *cInP) {
	int i, j, len = 0, top[2], cpos = 0;
	int heap[801];
	int connected[801];
	int singleDist[801];
	memset(connected, 0, sizeof(int) * 801);
	memset(singleDist, 0, sizeof(int) * 801);
	memset(heap, 0, sizeof(int) * 801);
	memset(values, ITF, sizeof(int) * 801);
	for(i = 1; i <= P; i++) {
		values[i] = dist[i][p];
		if (i == p) {
			values[i] = 0;
		}
		addNode(heap, ++len, i);
	}
	for(i = 1; i <= P; i++) {
		getTop(heap, len, top);
		connected[cpos++] = top[0];
		singleDist[top[0]] = top[1];
		
		for(j = 1; j <= N; j++) {
			if (top[0] == j || dist[top[0]][j]) continue;
		}
	}
}

main() {
	int dist[801][801];
	int cInP[801];
	int N, P, C;
	FILE* fin = fopen("butter.in", "r");
	FILE* fout = fopen("butter.out", "w");
	int i, j, k, v, f, t;
	int mindist = ITF;
	memset(cInP, 0, sizeof(int) * 801);
	for(i = 0; i < 801; i++) {
		for(j = 0; j < 801; j++) {
			dist[i][j] = ITF;
		}
		values[i] = ITF;
	}
	fscanf(fin, "%d %d %d", &N, &P, &C);
	for(i = 1; i <= N; i++) {
		fscanf(fin, "%d", &v);
		cInP[v]++;
	}

	for(i = 1; i <= C; i++) {
		fscanf(fin, "%d %d %d", &f, &t, &v);
		dist[f][t] = v;
		dist[t][f] = v;
	}

	for(k = 1; k <= P; k++) {
		for(i = 1; i <= P; i++) {
			for(j = 1; j <= P; j++) {
				if (dist[i][k] < ITF && dist[k][j] < ITF)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	for(i = 1; i <= P; i++) {
		dist[i][i] = ITF;
	}

	for(i = 1; i <= P; i++) {
		int runningmin = 0;
		for(j = 1; j <= P; j++) {
			if (i == j) continue;
			runningmin += dist[j][i] * cInP[j];
		}
		if (runningmin < mindist)
			mindist = runningmin;
	}

	fprintf(fout, "%d\n", mindist);

	exit(0);
}
