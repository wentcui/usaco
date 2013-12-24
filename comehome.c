/*
ID: wentcui1
LANG: C
TASK: comehome
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int matrix[256][256];


char findMin(int *dist, char *cand) {
	int i, minindex = 0;
	char min = cand[0];
	if (!min)
		return min;
	for(i = 0; cand[i]; i++) {
		if (dist[cand[i]] < dist[min]) {
			min = cand[i];
			minindex = i;
		}
	}

	cand[minindex] = cand[len - 1];
	return min;
}

main() {
	FILE *fin = fopen("comehome.in", "r");
	FILE* fout = fopen("comehome.out", "w");
	int i, d, pos = 0;
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
	for(i = 0; i < n; i++) {
		fscanf(fin, "%c %c %d", &f, &t, &d);
		matrix[f][t] = d;
		matrix[t][f] = d;

		if (dist[f] == 0) {
			cand[pos++] = f;
			dist[f] == 1;
		}
		if (dist[t] == 0 && t != 'Z'){
			cand[pos++] = t;
			dist[t] == 1;
		}
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
		matrix[m]['Z'] = dist[m];

		for (i = 'a'; i <= 'z'; i++) {
			if (matrix[m][i] != -1)
				dist[i] = min(dist[i], dist[m] + matrix[m][i]);
		}

		for (i = 'A'; i < 'Z'; i++) {
			if (matrix[m][i] != -1)
				dist[i] = min(dist[i], dist[m] + matrix[m][i]);
		}
	}

	char min = 'a';
	unsigned int minv = matrix[min]['Z'];
	for (i = 'a'; i <= 'z'; i++) {
		if (matrix[i]['Z'] < minv) {
			min = i;
			minv = matrix[i]['Z'];
		}
	}

	for (i = 'A'; i < 'Z'; i++) {
		if (matrix[i]['Z'] < minv) {
			min = i;
			minv = matrix[i]['Z'];
		}
	}

	printf("%c, %d\n", min, minv);
	exit(0);
}











