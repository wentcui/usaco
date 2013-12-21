/*
ID: wentcui1
LANG: C
TASK: concom
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int **shares;
int **control;

void find(int com) {
	int can, i, j;
	int *candidates = (int *)malloc(sizeof(int) * (n + 1));
	memset(candidates, 0, sizeof(int) * (n + 1));
	memcpy(candidates, shares[com], sizeof(int) * (n + 1));
	candidates[com] = -1;

	while(1) {
		can = -1;
		for(i = 1; i <= n; i++) {
			if (candidates[i] < 0) continue;
			if (candidates[i] > 50) {
				can = i;
				break;
			}
		}
		if (can < 0) break;

		//printf("%d %d\n", com, can);
		control[com][can] = 1;
		candidates[can] = -1;
		for(i = 1; i <= n; i++) {
			if (candidates[i] < 0 && can == i) continue;
			candidates[i] += shares[can][i];
		}		
	}
}

main() {
	int i, j, c1, c2, v;
	FILE *fin = fopen("concom.in", "r");
	FILE *fout = fopen("concom.out", "w");
	fscanf(fin, "%d", &n);
	int c = 100;

	shares = (int**)malloc(sizeof(int *) * (c + 1));
	control = (int**)malloc(sizeof(int *) * (c + 1));
	for(i = 0; i <= c; i++) {
		shares[i] = (int *)malloc(sizeof(int) * (c + 1));
		memset(shares[i], 0, sizeof(int) * (c + 1));

		control[i] = (int *)malloc(sizeof(int) * (c + 1));
		memset(control[i], 0, sizeof(int) * (c + 1));
	}

	for(i = 1; i <= n; i++) {
		fscanf(fin, "%d", &c1);
		fscanf(fin, "%d", &c2);
		fscanf(fin, "%d", &v);
		shares[c1][c2] = v;
		//printf("%d %d %d", c1, c2, v);
	}

	n = 100;

	for(i = 1; i <= n; i++) {
		find(i);
	}

	for(i = 1; i <= c; i++) {
		for(j = 1; j <= c; j++) {
			if (i != j && control[i][j] > 0)
				fprintf(fout, "%d %d\n", i, j);
		}
	}
	fclose(fout);
	exit(0);
}
