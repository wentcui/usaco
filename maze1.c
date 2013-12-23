/*
ID: wentcui1
LANG: C
TASK: maze1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char maze[201][77];
int h, w;

int min(int a, int b) {
	return (a < b) ? a : b;
}

int max(int a, int b) {
	return (a < b) ? b : a;
}

int canCross(int x1, int y1, int x2, int y2) {
	if (x2 < 0 || x2 >= h || y2 < 0 || y2 >= w)
		return 0;

	if (y1 < y2) {
		if (maze[2 * x1 + 1][2 * y1 + 2] == ' ')
			return 1;
	} else if (y1 > y2) {
		if (maze[2 * x1 + 1][2 * y2 + 2] == ' ')
			return 1;
	} else if (x1 < x2) {
		if (maze[2 * x1 + 2][2 * y1 + 1] == ' ')
			return 1;
	} else if (x1 > x2) {
		if (maze[2 * x2 + 2][2 * y1 + 1] == ' ')
			return 1;
	}
	return 0;
}

void getNh(int x, int y, int nh[4][2], int nodes[100][38]) {
	int pos = 0;
	if (canCross(x, y, x + 1, y) && nodes[x + 1][y] < 0) {
		nh[pos][0] = x + 1;
		nh[pos][1] = y;
		pos++;
	}

	if (canCross(x, y, x - 1, y) && nodes[x - 1][y] < 0) {
		nh[pos][0] = x - 1;
		nh[pos][1] = y;
		pos++;
	}

	if (canCross(x, y, x, y + 1) && nodes[x][y + 1] < 0) {
		nh[pos][0] = x;
		nh[pos][1] = y + 1;
		pos++;
	}

	if (canCross(x, y, x, y - 1) && nodes[x][y - 1] < 0) {
		nh[pos][0] = x;
		nh[pos][1] = y - 1;
		pos++;
	}
}

void incrAllNh(int x, int y, int nodes[100][38], int can_nodes[100][38]) {
	int nh[4][2];
	int i;
	for(i = 0; i < 4; i++) {
		nh[i][0] = -1;
	}
	getNh(x, y, nh, nodes);

	for(i = 0; i < 4 && nh[i][0] >= 0; i++) {
		can_nodes[nh[i][0]][nh[i][1]] = 
			min(can_nodes[nh[i][0]][nh[i][1]], can_nodes[x][y] + 1);
	}
}

void getMinNode(int nodes[100][38], int *x, int *y) {
	int i, j;
	int min = 4000;
	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) {
			if (nodes[i][j] < min) {
				min = nodes[i][j];
				*x = i;
				*y = j;
			}
		}
	}
}

void findMaxDist(int sx, int sy, int nodes[100][38]) {
	int i, j;
	int mx, my;
	int can_nodes[100][38];
	int max = -1;
	for(i = 0; i < 100; i++) {
		for(j = 0; j < 38; j++) {
			nodes[i][j] = -1;
			can_nodes[i][j] = 4000;
		}
	}

	can_nodes[sx][sy] = 0;
	while(1) {
		mx = my = -1;
		getMinNode(can_nodes, &mx, &my);
		if (mx == -1 || my == -1)
			break;

		nodes[mx][my] = can_nodes[mx][my];
		incrAllNh(mx, my, nodes, can_nodes);
		can_nodes[mx][my] = 4000;
	}
}

main() {
	int i, j;
	FILE *fin = fopen("maze1.in", "r");
	FILE *fout = fopen("maze1.out", "w");
	int p1x = -1, p1y = 1, p2x = -1, p2y = -1;
	int nodes1[100][38], nodes2[100][38];
	int max = 0;

	for(i = 0; i < 201; i++) {
		for(j = 0; j < 77; j++) {
			maze[i][j] = '\0';
		}
	}

	fscanf(fin, "%d %d", &w, &h);
	fgetc(fin);

	for(i = 0; i < 2 * h + 1; i++) {
		for(j = 0; j < 2 * w + 1; j++) {
			fscanf(fin, "%c", &maze[i][j]);
			if ((i == 0 || i == 2 * h || j == 0 || j == 2 * w) 
					&& maze[i][j] == ' ') {
				if (p1x == -1) {
					p1x = (i - 1) / 2;
					p1y = (j - 1) / 2;
				} else if (p2x == -1) {
					p2x = (i - 1) / 2;
					p2y = (j - 1) / 2;
				}
			}

		}
		if (i < 2 * h)
			fgetc(fin);
	}

	findMaxDist(p1x, p1y, nodes1);
	findMaxDist(p2x, p2y, nodes2);

	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) {
			int m = min(nodes1[i][j], nodes2[i][j]);
			if (m > max)
				max = m;
		}
	}
	fprintf(fout, "%d\n", max + 1);
	fclose(fout);
	exit(0);
}
