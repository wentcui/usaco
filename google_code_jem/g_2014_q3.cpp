#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

int main() {
	FILE *fin = fopen("q3.in", "r");
	FILE *fout = fopen("q3.out", "w");
	char res[1001][1001];
	int cases, caseno = 0;
	int R, C, M, ss, lm, sq, lq;
	int i, j, k;
	bool stat = false, check = false;
	fscanf(fin, "%d", &cases);
	while(cases--) {
		i = j = lm = 0;
		stat = false;
		check = true;
		fscanf(fin, "%d %d %d", &R, &C, &M);
		if (M == R * C - 1) {
			check = false;
			stat = true;
		} else if (min(R, C) == 1) {
			check = false;
			stat = true;
			i = 1;
			j = R * C - M;
		}
		for(i = 2; i <= min(R, C) && check; i++) {
			for(j = i; j <= max(R, C); j++) {
				ss = R * C - M;
				lm = i * j - ss;
				//printf("%d %d %d %d\n", i, j, ss, lm);
				if (lm < 0)	continue;
				if (lm >= min(R, C))	break;
				if (!lm) {
					stat = true;
					break;
				}
				lq = sq = (int)sqrt(lm);
				if (sq * sq < lm)
					sq++;

				if (lq * (lq - 1) >= lm)
					lq--;
				if (i - lq < 2)
					break;
				if (j - sq >= 2) {
					stat = true;
					break;
				}
			}
			if (stat)	break;
		}
		fprintf(fout, "Case #%d:\n", ++caseno);
		if (!stat) {
			fprintf(fout, "Impossible\n");
			continue;
		}
		for(int x = 0; x < max(R, C); x++)
		for(int y = 0; y < min(R, C); y++) {
			if (x < j && y < i)
				res[x][y] = '.';
			else
				res[x][y] = '*';
		}
		if (R * C != M)
			res[0][0] = 'c';
		for(int y = i - 1; y >= i - sq && lm > 0; y--)
		for(int x = j - 1; x >= j - sq && lm > 0; x--) {
			res[x][y] = '*';
			lm--;
		}

		if (R == max(R, C)) {
			for(int x = 0; x < max(R, C); x++) {
				for(int y = 0; y < min(R, C); y++) {
					fprintf(fout, "%c", res[x][y]);
				}
				fprintf(fout, "\n");
			}
		} else {
			for(int y = 0; y < min(R, C); y++) {
				for(int x = 0; x < max(R, C); x++) {
					fprintf(fout, "%c", res[x][y]);
				}
				fprintf(fout, "\n");
			}
		}
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
