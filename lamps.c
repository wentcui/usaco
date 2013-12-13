/*
ID: wentcui1
LANG: C
TASK: lamps
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, count;
int finalon[101], finaloff[101];
long int gotOne = 0;
FILE *fout;

void outputSingle(char c, int left) {
	int j = 0;
	while (j < 8 && j <= left) {
		fprintf(fout, "%d", (c & (1 << j)) > 0);
		j++;
	}
}

void flip(char *arr, int type) {
	int i;
	char mask = '\0';
	switch(type) {
		case 1: mask = 0xFF; break;
		case 2: mask = 0x55; break;
		case 3: mask = 0xAA; break;
		case 4: mask = 0x49; break;
		default: break;
	}

	if (type <= 3) {
		for(i = 0; i <= (n - 1) / 8; i++)
			arr[i] ^= mask;
	} else {
		for(i = 0; i <= (n - 1) / 8; i++) {
			arr[i] ^= (mask << (i % 3));
		}
	}
}


int checkBit(char *arr, int pos) {
	return (arr[(pos - 1) / 8] & (1 << ((pos - 1) % 8))) > 0;
}


int validate(char *arr) {
	int i = 0;
	for(i = 0; finalon[i]; i++)
		if (!checkBit(arr, finalon[i])) {
			return 0;
		}
	
	for(i = 0; finaloff[i]; i++)
		if (checkBit(arr, finaloff[i])) {
			return 0;
		}
	return 1;
}


void output(char *arr) {
	int i = 1, j = 0, nr = 0;
	char c = '\0';
	while (i <= n) {
		c = arr[nr];
		outputSingle(c, n - i);
		i += 8;
		nr++;
	}
	fprintf(fout, "\n");
}

void dfs(char *arr, int curtype, int curcount) {
	int i = 0;
	if (curcount > count) {
		if (validate(arr)) {
			output(arr);
			gotOne++;
		}
		return;
	}
	if (curtype > 4)
		return;

	for(i = 1; i <= count; i++) {
		flip(arr, curtype);
		dfs(arr, curtype + 1, curcount + 1);
	}

	if (i % 2)
		flip(arr, curtype);
	dfs(arr, curtype + 1, curcount);
}

main() {
	FILE* fin = fopen("lamps.in", "r");
	fout = fopen("lamps.out", "w");
	int i, j, k, l, pos;
	char *arr;
	fscanf(fin, "%d", &n);
	fgetc(fin);
	fscanf(fin, "%d", &count);
	fgetc(fin);

	arr = (char *)malloc(sizeof(char) * ((n - 1) / 8 + 1));

	memset(finalon, 0, sizeof(int) * 101);
	memset(finaloff, 0, sizeof(int) * 101);
	memset(arr, 0xFF, sizeof(char) * ((n - 1) / 8 + 1));

	i = 0;
	fscanf(fin, "%d", &pos);
	while(pos != -1) {
		finalon[i++] = pos;
		fscanf(fin, "%d", &pos);
	}

	fgetc(fin);
	i = 0;
	fscanf(fin, "%d", &pos);
	while(pos != -1) {
		finaloff[i++] = pos;
		fscanf(fin, "%d", &pos);
	}

	dfs(arr, 1, 1);
	if (!gotOne) {
		fprintf(fout, "IMPOSSIBLE\n");
	}
	fclose(fout);
	exit(0);
}
