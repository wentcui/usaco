/*
ID: wentcui1
LANG: C++
TASK: agrinet
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
struct vnode varr[10000];

int compare(const void *x, const void *y) {
	struct vnode *_x = (struct vnode*)x;
	struct vnode *_y = (struct vnode*)y;
	return _x->v - _y->v;
}

int dfs(int p, int **resmatrix, int* visited, int step) {
	int i;
	if (visited[p]) {
		if (step - visited[p] == 2)
			return 0;
		return 1;
	}
	visited[p] = step;
	for(i = 1; i <= n; i++) {
		if (resmatrix[p][i] < ITF && dfs(i, resmatrix, visited, step + 1))
			return 1;
	}
	visited[p] = 0;
	return 0;
}

int checkloop(int **resmatrix) {
	int i, step = 1;
	int *visited = (int*)malloc(sizeof(int) * (n + 1));
	memset(visited, 0, sizeof(int) * (n + 1));
	for(i = 1; i <= n; i++) {
		if (!visited[i] && dfs(i, resmatrix, visited, step))
			return 1;
	}
	return 0;
}

main() {
	FILE* fin = fopen("agrinet.in", "r");
	FILE* fout = fopen("agrinet.out", "w");
	int i, j, pos = 0;
	fscanf(fin, "%d", &n);
	int **matrix = (int**)malloc(sizeof(int*) * (n + 1));
	int **resmatrix = (int**)malloc(sizeof(int*) * (n + 1));
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
				varr[pos].a = i;
				varr[pos].b = j;
				varr[pos].v = matrix[i][j];
				pos++;
			}
		}
	}

	qsort(varr, pos, sizeof(struct vnode), compare);

	i = 1;
	j = 0;
	int sum = 0;
	while(i < n) {
		struct vnode *n = &varr[j++];
		printf("%d %d %d\n", n->a, n->b, n->v);
		sum += n->v;
		resmatrix[n->a][n->b] = n->v;
		resmatrix[n->b][n->a] = n->v;
		if(checkloop(resmatrix)) {
			sum -= n->v;
			printf("loop: %d %d\n", n->a, n->b);
			resmatrix[n->a][n->b] = ITF;
			resmatrix[n->b][n->a] = ITF;
			continue;
		}
		i++;
	}
	fprintf(fout, "%d\n", sum);
	fclose(fout);
	exit(0);
}
