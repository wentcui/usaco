/*
ID: wentcui1
LANG: C
TASK: contact
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int16_t str[12501];
int rec[8193];
int len = 0;

struct node {
	int a;
	int v;
};

struct node narr[8193];
FILE* fin;
FILE* fout;

int compare(const void* x, const void* y) {
	struct node *nx = (struct node *)x;
	struct node *ny = (struct node *)y;

	if (nx->v != ny->v)
		return ny->v - nx->v;
	return nx->a - ny->a;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int __getbits(int16_t v, int a, int b) {
	int ret = 0;
	while(a <= b) {
		ret = (ret << 1) + ((v & (1 << a)) >> a);
		a++;
	}
	return ret;
}

// start from 0 to 15
int getbits(int f, int t) {
	int ret = 1 << (t - f + 1), i;
	int fi = f / 16;
	int ti = t / 16;
	int vi = str[fi];
	int start = f % 16;
	int end = t % 16;

	if (start <= end)
		return ret + __getbits(vi, start, end);
	else
		return ret + (__getbits(vi, start, 15) << (end + 1)) + __getbits(str[fi + 1], 0, end); 
}

void printbinary(int v) {
	int mask = (1 << 15);
	while(!(mask & v)) {
		mask = mask >> 1;
	}
	mask = mask >> 1;
	while(mask > 0) {
		fprintf(fout, "%d", (v & mask) > 0);
		mask = mask >> 1;
	}
}

main() {
	fin = fopen("contact.in", "r");
	fout = fopen("contact.out", "w");
	int pos = 0, lastv, count;

	memset(str, 0, sizeof(int16_t) * 12501);
	memset(rec, 0, sizeof(int) * 4097);
	int a, b, n;
	int i, j, k, done = 0;
	fscanf(fin, "%d %d %d", &a, &b, &n);
	fgetc(fin);

	while(!done) {
		for(i = 0; i < 5 && !done; i++) {
			int16_t v = 0;
			for(j = 0; j < 16; j++) {
				char c = '\n';
				int vi = 0;
				fscanf(fin, "%c", &c);
				if (c == '0' || c == '1') {
					vi = c - '0';
					v |= (vi << j);
					len++;
				}

				if (feof(fin)) {
					done = 1;
					break;
				}
			}
			str[pos++] = v;
		}
		fgetc(fin);
	}


	for(i = a; i <= b; i++) {
		for(k = 0; k <= len - i; k++) {
			int v = getbits(k, k + i - 1);
			rec[v]++;
		}
	}

	pos = 0;
	for(i = 0; i < 8193; i++) {
		if (rec[i] > 0) {
			narr[pos].a = i;
			narr[pos].v = rec[i];
			pos++;
		}
	}
	qsort(narr, pos, sizeof(struct node), compare);

	int init = 1;
	int finished = 1;
	count = 1;
	pos = 0;
	lastv = 0;
	while(n > 0 || !finished)  {	
		if (narr[pos].v < 1)
			break;
		if (lastv != narr[pos].v) {
			lastv = narr[pos].v;
			count = 1;
			if (!init) {
				fprintf(fout, "\n");
			}
			init = 0;
			fprintf(fout, "%d\n", lastv);
			printbinary(narr[pos].a);
			n--;
		} else {
			count++;
			if (count != 1)
    			fprintf(fout, " ");
			printbinary(narr[pos].a);
			if (count == 6) {
				if (narr[pos + 1].v == lastv)
					fprintf(fout, "\n");
				count = 0;
			}
		}
		pos++;

		if (n == 0) {
			if (narr[pos].v == lastv)
				finished = 0;
			else
				finished = 1;
		}
	}
	fprintf(fout, "\n");
	fclose(fout);

	exit(0);
}
