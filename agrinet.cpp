/*
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITF 200000
int n;

struct vnode{
	int a;
	int b;
	int v;
};
struct vnode* varr[10000];

int compare(const void *x, const void *y) {
	return ((struct vnode *)x)->v - ((struct vnode *)y)->v;
}

int dfs(int p, int **resmatrix, int* visited) {
	int i;
	if (visited[p])
		return 1;
	visited[p] = 1;
	for(i = 1; i <= n; i++) {
		if (resmatrix[p][i] < ITF && dfs(i, resmatrix, visited))
			return 1;
	}
	return 0;
}

int checkloop(int **resmatrix) {
	int i;
	int *visited = (int*)malloc(sizeof(int) * (n + 1));
	memset(visited, 0, sizeof(int) * (n + 1));
	for(i = 1; i <= n; i++) {
		if (!visited[i] && dfs(i, resmatrix, visited))
			return 1;
	}
	return 0;
}

main() {
	FILE* fin = fopen("agrinet.in", "r");
	FILE* fout = fopen("agrinet.out", "w");
	int i, j, pos = 0;
	printf("dddddddddddddd\n");
	fscanf(fin, "%d", &n);
	printf("readin: %d\n", n);
	int **matrix = (int**)malloc(sizeof(int*) * (n + 1));
	int **resmatrix = (int**)malloc(sizeof(int*) * (n + 1));
	printf("hi1\n");
	for(i = 0; i <= n; i++) {
		matrix[i] = (int *)malloc(sizeof(int) * (n + 1));
		resmatrix[i] = (int *)malloc(sizeof(int) * (n + 1));
		for(j = 0; j <= n; j++) {
			matrix[i][j] = ITF;
			resmatrix[i][j] = ITF;
		}
	}
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			fscanf(fin, "%d", &matrix[i][j]);
			if (i < j) {
				struct vnode *n = (struct vnode *)malloc(sizeof(struct vnode));
				n->a = i;
				n->b = j;
				n->v = matrix[i][j];
				printf("%d %d %d\n", i, j, matrix[i][j]);
				varr[pos++] = n;
			}
		}
		printf("\n");
	}

	qsort(varr, pos, sizeof(struct vnode *), compare);
	printf("hi2\n");
	if (!varr) {
		printf("WTF\n");
		return 1;
	}

	i = 1;
	j = 0;
	while(i < n) {
		struct vnode *n = varr[j++];
		printf("%d %d %d\n", n->a, n->b, n->v);
		resmatrix[n->a][n->b] = n->v;
		if(checkloop(resmatrix)) {
			resmatrix[n->a][n->b] = ITF;
			continue;
		}
		i++;
	}
}
