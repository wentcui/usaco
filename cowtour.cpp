/*
ID: wentcui1
LANG: C++
TASK: cowtour
*/
#include <stdio.h>
#include <math.h>
#define ITF (1e40)

double dis[200][200];
double dt[200];
int px[200], py[200];
int n;

double min(double a, double b) {
	return a > b ? b : a;
}

double dist(int& x1, int& y1, int& x2, int& y2) {
	return sqrt((double)(x1 - x2) * (x1 - x2) + (double)(y1 - y2) * (y1 - y2));
}

void floyd() {
	int i, j, k;
	for(k = 1; k <= n; k++) {
		for(i = 1; i <= n; i++) {
			for(j = 1; j <= n; j++) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
				//if (dis[i][k] + dis[k][j] < dis[i][j])
				//	dis[i][j] = dis[i][k] + dis[k][j];
			}
		}
	}

	for(i = 1; i <= n; i++) {
		dis[i][i] = ITF;
	}
}

int main() {
	int i, j, a;
	double max = 0, rmax = 0, newmin = ITF;
	FILE * fin = fopen("cowtour.in", "r");
	FILE * fout = fopen("cowtour.out", "w");
	fscanf(fin, "%d", &n);
	for(i = 1; i <= n; i++) {
		fscanf(fin, "%d %d", &px[i], &py[i]);
	}
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			a = 10;
			while(a == 10 || a == 13)
				a = getc(fin);
			a -= 48;
			if (a) { 	
				dis[i][j] = dist(px[i], py[i], px[j], py[j]);
			} else	dis[i][j] = ITF;
		}
	}
	floyd();
	for(i = 1; i <= n; i++) {
		rmax = 0;
		for(j = 1; j <= n; j++) {
			if (dis[i][j] != ITF && dis[i][j] > rmax) {
				rmax = dis[i][j];
			}
		}
		dt[i] = rmax;
		if (rmax > max)
			max = rmax;
	}

	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			if (i != j && dis[i][j] == ITF) {
				double d = dist(px[i], py[i], px[j], py[j]);
				if (dt[i] + dt[j] + d < newmin)
					newmin = dt[i] + dt[j] + d;
			}
		}
	}

	fprintf(fout, "%.6lf\n", newmin > max ? newmin : max);
	fclose(fin);
	fclose(fout);
	return 0;
}















