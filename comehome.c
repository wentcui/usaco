/*
ID: wentcui1
LANG: C
TASK: comehome
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int matrix[256][256];

int min(unsigned int a, unsigned int b) {
	return a > b ? b : a;
}

char findMin(unsigned int *dist, char *cand) {
	unsigned int minv = 0xffffffff;
	int minindex = 0, i;
	char ret;

	if (!cand[0] || !cand[1]) {
		cand[0] = '\0';
		return cand[0];
	}

	for(i = 0; cand[i]; i++) {
		if (dist[cand[i]] >= 0 && dist[cand[i]] < minv) {
			minv = dist[cand[i]];
			minindex = i;
			ret = cand[i];
		}
	}

	cand[minindex] = cand[i - 1];
	cand[i - 1] = '\0';
	return ret;
}

main() {
	FILE *fin = fopen("comehome.in", "r");
	FILE* fout = fopen("comehome.out", "w");
	int i, j, d, pos = 0;
	char f, t;
	unsigned int dist[256];
	char cand[256];

	memset(dist, 0, sizeof(unsigned int) * 256);
	memset(cand, '\0', sizeof(char) * 256);
	for(i = 0; i < 256; i++) {
		for(j = 0; j < 256; j++) {
			matrix[i][j] = -1;
		}
	}
	int n;
	fscanf(fin, "%d", &n);
	fgetc(fin);
	for(i = 0; i < n; i++) {
		fscanf(fin, "%c %c %d", &f, &t, &d);
		if (matrix[f][t] == -1 || d < matrix[f][t]) {
			matrix[f][t] = d;
			matrix[t][f] = d;
		}

		if (dist[f] == 0) {
			cand[pos++] = f;
			dist[f] = 1;
		}
		if (dist[t] == 0 && t != 'Z'){
			cand[pos++] = t;
			dist[t] = 1;
		}
		if (i < n - 1)
			fgetc(fin);
	}

	memset(dist, 0xffffffff, sizeof(unsigned int) * 256);
	for(i = 'A'; i < 'Z'; i++) {
		if (matrix[i]['Z'] > 0)
			dist[i] = matrix[i]['Z'];
	}

	for(i = 'a'; i <= 'z'; i++) {
		if (matrix[i]['Z'] > 0)
			dist[i] = matrix[i]['Z'];
	}

	while(1) {
		char m = findMin(dist, cand);
		if (!m) break;

		matrix[m]['Z'] = dist[m];

		for (i = 'a'; i <= 'z'; i++) {
			if (matrix[i][m] != -1) {
				dist[i] = min(dist[i], dist[m] + matrix[i][m]);
			}
		}

		for (i = 'A'; i < 'Z'; i++) {
			if (matrix[i][m] != -1) {
				dist[i] = min(dist[i], dist[m] + matrix[i][m]);
			}
		}
	}

	char minc;
	unsigned int minv = 0xffffffff;
	for (i = 'A'; i < 'Z'; i++) {
		if (matrix[i]['Z'] > 0 && matrix[i]['Z'] < minv) {
			minc = i;
			minv = matrix[i]['Z'];
		}
	}

	fprintf(fout, "%c %d\n", minc, minv);
	exit(0);
}











