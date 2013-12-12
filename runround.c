/*
ID: wentcui1
LANG: C
TASK: runround
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(int *arr, int len) {
	int start = 0, end = len - 1;
	while(start < end) {
		int temp = arr[start];
		arr[start++] = arr[end];
		arr[end--] = temp;
	}
}

int checkRound(unsigned long int val) {
	unsigned int visited = 1;
	int index = 0, nextindex = 0;
	int pos = 0, count = 0;
	int num[10];
	memset(num, 0, 10);
	while(val > 0) {
		int d = val % 10;
		if (visited & (1 << d))
			return 0;
		visited |= (1 << d);
		num[pos++] = d;
		count++;
		val /= 10;
	}

	reverse(num, pos);
	visited = 0;
	index = 0;
	while(1) {
		nextindex = index + num[index];
		if (nextindex >= pos)
			nextindex %= pos;

		if (visited & (1 << num[nextindex]))
			return 0;
		visited |= (1 << num[nextindex]);
		count--;
		if (!count)
			return 1;
		index = nextindex;
	}
	return 1;
}

main()
{
	unsigned long int n;
	FILE *fin = fopen("runround.in", "r");
	FILE *fout = fopen("runround.out", "w");
	fscanf(fin, "%lu", &n);
	while (!checkRound(n + 1))
		n++;

	fprintf(fout, "%lu\n", n + 1);
	exit(0);
}
