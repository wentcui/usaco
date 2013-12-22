/*
ID: wentcui1
LANG: C
TASK: ttwo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s1 = 0x01;
char s2 = 0x02;
char s3 = 0x04;
char s4 = 0x08;

char Fstat[10][10];

char Cstat[10][10];


int validate_pos(int x, int y, char stat[10][10]) {
	if (x < 0 || x >= 10 || y < 0 || y >= 10 || stat[x][y] == '*')
		return 0;
	return 1;
}

void getNextStat(int *x, int *y, char *s, char stat[10][10]) {
	if (*s == s1) {
		if (!validate_pos(*x, (*y) + 1, stat))
			*s = s2;
		else
			(*y)++;
	}
	else if (*s == s2) {
		if (!validate_pos((*x) + 1, *y, stat))
			*s = s3;
		else
			(*x)++;
	}
	else if (*s == s3) {
		if (!validate_pos(*x, (*y) - 1, stat))
			*s = s4;
		else
			(*y)--;
	}
	else if (*s == s4) {
		if (!validate_pos((*x) - 1, *y, stat))
			*s = s1;
		else
			(*x)--;
	}
}

main() {
	FILE *fin = fopen("ttwo.in", "r");
	FILE *fout = fopen("ttwo.out", "w");
	int i, j;
	int cx, cy, fx, fy;
	char cs = s4, fs = s4;
	char stat[10][10];
	int count = 0;
	int crashCount = 0;
	for (i = 0; i < 10; i++) {
		for(j = 0; j < 10; j++) {
			fscanf(fin, "%c", &stat[i][j]);
			if (stat[i][j] == 'F') {
				fx = i, fy = j;
			} else if (stat[i][j] == 'C') {
				cx = i, cy = j;
			}
		}
		if (i < 9)
			fgetc(fin);
	}

	memset(Fstat, 0x00, sizeof(char) * 10 * 10);
	memset(Cstat, 0x00, sizeof(char) * 10 * 10);
	while(1) {
		if ((Fstat[fx][fy] & fs) && (Cstat[cx][cy] & cs)) {
			crashCount++;
			if (crashCount > 100) {
				count = 0;
			//printf("%d %d %d %d\n", fx, fy, fs, Fstat[fx][fy]);
			//printf("%d %d %d %d\n", cx, cy, cs, Cstat[cx][cy]);
				break;
			}
		}
		if (fx == cx && fy == cy)
			break;

		count++;
		//printf("%d\n", count);


		Fstat[fx][fy] |= fs;
		Cstat[cx][cy] |= cs;

		//printf("*%d %d %d %d\n", fx, fy, fs, Fstat[fx][fy]);
		//printf("*%d %d %d %d\n", cx, cy, cs, Cstat[cx][cy]);

		getNextStat(&fx, &fy, &fs, stat);
		getNextStat(&cx, &cy, &cs, stat);
	}
	fprintf(fout, "%d\n", count);
	fclose(fout);
	exit(0);
}
