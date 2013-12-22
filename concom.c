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
int *candidates;
int candidates_nr = 0;

void find(int com) {
	int *cand = (int *)malloc(sizeof(int) * (n + 1));
	int *cand_shares = (int *)malloc(sizeof(int) * (n + 1));
	int cand_pos = candidates_nr, cid, i;
	memcpy(cand, candidates, sizeof(int) * candidates_nr);

	for(i = 0; i < cand_pos; i++) {
		cand_shares[cand[i]] = shares[com][cand[i]];
	}
	
	while(1) {
		cid = -1;
		for(i = 0; i < cand_pos; i++) {
			if (cand[i] == com) {
				cand[i] = cand[--cand_pos];
			}
			if (cand_shares[cand[i]] > 50) {
				cid = cand[i];
				cand[i] = cand[--cand_pos];
				break;
			}
		}
		if (cid < 0)	break;

		control[com][cid] = 1;

		for(i = 0; i < cand_pos; i++) {
			cand_shares[cand[i]] += shares[cid][cand[i]];
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
	candidates = (int *)malloc(sizeof(int) * (c + 1));
	int *map = (int *)malloc(sizeof(int) * (c + 1));
	memset(map, 0, sizeof(int) * (c + 1));
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
		if (!map[c1]) {
			candidates[candidates_nr++] = c1;
			map[c1] = 1;
		}

		if (!map[c2]) {
			candidates[candidates_nr++] = c2;
			map[c2] = 1;
		}
	}

	for(i = 0; i < candidates_nr; i++) {
		find(candidates[i]);
	}

	for(i = 1; i <= 100; i++) {
		for(j = 1; j <= 100; j++) {
			if (i != j && control[i][j] > 0)
				fprintf(fout, "%d %d\n", i, j);
		}
	}
	fclose(fout);
	exit(0);
}
