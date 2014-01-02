/*
ID: wentcui1
LANG: C
TASK: butter
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITF 200000000

int min(int a, int b) {
	return a > b ? b : a;
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
