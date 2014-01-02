/*
ID: wentcui1
LANG: C
TASK: ratios
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fin, *fout;
int fff = 1;

int validate(int rec[4][3]) {
	int i, j, k;
	int temp1[3];
	temp1[0] = rec[0][0], temp1[1] = rec[0][1], temp1[2] = rec[0][2];
	for(i = 0; rec[0][0] >= 0 && rec[0][1] >= 0 && rec[0][2] >= 0; i++) {
		int temp2[3];
		if (i > 0)
			rec[0][0] -= rec[1][0], rec[0][1] -= rec[1][1], rec[0][2] -= rec[1][2];
		temp2[0] = rec[0][0], temp2[1] = rec[0][1], temp2[2] = rec[0][2];
		for(j = 0; rec[0][0] >= 0 && rec[0][1] >= 0 && rec[0][2] >= 0; j++) {
			int temp3[3];
			if (j > 0)
				rec[0][0] -= rec[2][0], rec[0][1] -= rec[2][1], rec[0][2] -= rec[2][2];
			temp3[0] = rec[0][0], temp3[1] = rec[0][1], temp3[2] = rec[0][2];
			for(k = 0; rec[0][0] >= 0 && rec[0][1] >= 0 && rec[0][2] >= 0; k++) {
				if (k > 0)
					rec[0][0] -= rec[3][0], rec[0][1] -= rec[3][1], rec[0][2] -= rec[3][2];
				if (!rec[0][0] && !rec[0][1] && !rec[0][2]) {
					fprintf(fout, "%d %d %d %d\n", i, j, k, fff);
					return 1;
				}
			}
			rec[0][0] = temp3[0], rec[0][1] = temp3[1], rec[0][2] = temp3[2];
		}
		rec[0][0] = temp2[0], rec[0][1] = temp2[1], rec[0][2] = temp2[2];
	}
	rec[0][0] = temp1[0], rec[0][1] = temp1[1], rec[0][2] = temp1[2];
	return 0;
}

main() {
	fin = fopen("ratios.in", "r");
	fout = fopen("ratios.out", "w");
	int rec[4][3];
	int i, j;
	for(i = 0; i < 4; i++) {
		fscanf(fin, "%d %d %d", &rec[i][0], &rec[i][1], &rec[i][2]);
	}

	int a = rec[0][0], b = rec[0][1], c = rec[0][2];
	while(fff < 100) {
		if (validate(rec))
			exit(0);
		rec[0][0] += a, rec[0][1] += b, rec[0][2] += c;
		fff++;
	}
	if (fff == 100)
		fprintf(fout, "NONE\n");
	exit(0);
}







