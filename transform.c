#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match90(char **ori, char **tra, int layer, int n) {
	int i = 0;
	for(i = layer; i < n - layer; i++) {
		if (ori[layer][i] != tra[i][n - layer - 1])
			return -1;
		if (ori[i][n - layer - 1] != tra[n - layer - 1][n - i - 1])
			return -1;
		if (ori[n - layer - 1][n - i - 1] != tra[n - i - 1][layer])
			return -1;
		if (ori[n - i - 1][layer] != tra[layer][i])
			return -1;
	}
	return 1;
}

int match180(char **ori, char **tra, int layer, int n) {
	int i = 0;
	for(i = layer; i < n - layer; i++) {
		if (ori[layer][i] != tra[n - layer - 1][n - i - 1])
			return -1;
		if (ori[i][n - layer - 1] != tra[n - i - 1][layer])
			return -1;
		if (ori[n - layer - 1][n - i - 1] != tra[layer][i])
			return -1;
		if (ori[n - i - 1][layer] != tra[i][n - layer - 1])
			return -1;
	}
	return 2;
}

int match270(char **ori, char **tra, int layer, int n) {
	int i = 0;
	for(i = layer; i < n - layer; i++) {
		if (ori[layer][i] != tra[n - i - 1][layer])
			return -1;
		if (ori[i][n - layer - 1] != tra[layer][i])
			return -1;
		if (ori[n - layer - 1][n - i - 1] != tra[i][n - layer - 1])
			return -1;
		if (ori[n - i - 1][layer] != tra[n - layer - 1][n - i - 1])
			return -1;
	}
	return 3;
}

int match(char **ori, char **tra, int n) {
	int i, j, layer, left = 3;
	int res[3];
	res[0] = 1;
	res[1] = 2;
	res[2] = 3;
	layer = (n - 1) / 2;

	while(layer >= 0) {
		j = 0;
		while(j < left) {
			if (res[j] == 1) {
				if (match90(ori, tra, layer, n) < 0) {
					res[j] = res[--left];
				} else {
					j++;
				}	
			} else if (res[j] == 2) {
				if (match180(ori, tra, layer, n) < 0) {
					res[j] = res[--left];
				} else {
					j++;
				}
			} else if (res[j] == 3) {
				if (match270(ori, tra, layer, n) < 0) {
					res[j] = res[--left];
				} else {
					j++;
				}
			}
		}
		if (left <= 0)
			break;
		layer--;
	}
	if (left > 0)
		return res[0];
	for(i = 0; i < n; i++) {
		if (strcmp(ori[i], tra[i]))
			break;
	}
	if (i == n)
		return 6;
	return -1;
}

void reflect(char **ori, int n) {
	int i, j;
	char temp;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n / 2; j++) {
			temp = ori[i][j];
			ori[i][j] = ori[i][n - j - 1];
			ori[i][n - j - 1] = temp;
		}
	}
}

main() {
	FILE *fin, *fout;
	int n, i, ret;
	char **ori, **tra;
	fin = fopen("transform.in", "r");
	fout = fopen("transform.out", "w");

	fscanf(fin, "%d", &n);
	fgetc(fin);
	ori = (char **)malloc(sizeof(char *) * (n + 1));
	tra = (char **)malloc(sizeof(char *) * (n + 1));
	for(i = 0; i < n; i++) {
		ori[i] = (char *)malloc(n + 1);
		memset(ori[i], '\0', n);
		tra[i] = (char *)malloc(n + 1);
	}
	for(i = 0; i < n; i++) {
		fgets(ori[i], n + 1, fin);
		fgetc(fin);
	}
	for(i = 0; i < n; i++) {
		fgets(tra[i], n + 1, fin);
		fgetc(fin);
	}

	ret = match(ori, tra, n);
	if (ret > 0) {
		fprintf(fout, "%d\n", ret);
		exit(0);
	}
	reflect(ori, n);

	for(i = 0; i < n; i++) {
		if (strcmp(ori[i], tra[i]))
			break;
	}
	if (i == n) {
		fprintf(fout, "4\n");
		exit(0);
	}
	ret = match(ori, tra, n);
	if (ret > 0) {
		fprintf(fout, "5\n");
		exit(0);
	}
	fprintf(fout, "7\n");
	exit(0);
}
