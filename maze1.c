/*
ID: wentcui1
LANG: C
TASK: maze1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char maze[201][77];
int p1 = -1, p2 = -1;
int candidates[4000];
int h, w;

void findAllDist() {
	
}

main() {
	int i, j;
	FILE *fin = fopen("maze1.in", "r");
	FILE *fout = fopen("maze1.out", "w");

	memset(maze, '\0', sizeof(char) * 201 * 77);

	fscanf("%d %d", &w, &h);
	fgetc(fin);

	for(i = 0; i < 2 * h + 1; i++) {
		for(j = 0; j < 2 * w + 1; j++) {
			fscanf(fin, "%c", &maze[i][j]);
		}
		if (i < h - 1)
			fgetc(fin);
	}

	for(i = 0; i < 2 * w + 1; i++) {
		if (maze[0][i] == ' ') {
			if (p1 == -1)
				p1 = i / 2;
			else {
				p2 = i / 2;
				break;
			}
		}

		if (maze[2 * h][i] == ' ') {
			if (p1 == -1)
				p1 = (h - 1) * w + (i / 2)
			else {
				p2 = (h - 1) * w + (i / 2);
				break;
			}
		}
	}
	for(i = 0; i < 2 * h + 1 && p2 < 0; i++) {
		if (maze[i][0] == ' ') {
			if (p1 == -1)
				p1 = (i / 2 - 1) * w;
			else {
				p2 = 
			}
		}
	}
}




















