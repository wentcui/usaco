/*
ID: wentcui1
LANG: C
TASK: beads
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int expand_head(char *str, int index)
{
	int ret = 0;
	if (!index)
		return ret;
	while(index > 0 && str[index - 1] == 'w') {
		ret++;
		index--;
	}
	return ret;
}

int expand(char *str, int index)
{
	char last = *(str + index);
	int nextindex = index;
	while(*(str + nextindex) && 
			(*(str + nextindex) == 'w' || *(str + nextindex) == last)) {
		nextindex++;
		if (*(str + nextindex) != 'w' && last == 'w')
			last = *(str + nextindex);
	}

	return nextindex;
}
main(void) {
    int n, i, max = 0, runningmax = 0;
	int prevlen = 0, nextlen = 0;
	char *str;
	char last;
    FILE *fin  = fopen("beads.in", "r");
    FILE *fout = fopen("beads.out", "w");
	fscanf(fin, "%d", &n);
	fgetc(fin);
	str = (char *)malloc(sizeof(char) * (2 * n + 1));
	if (!str)
		exit(0);
	memset(str, '\0', 2 * n + 1);
	fgets(str, n + 1, fin);
	for(i = 0; i < n; i++) {
		str[n + i] = str[i];
	}

	last = *str;
	for(i = 0; i < n; i++) {
		if (str[i] != 'w' && last == 'w')
			last = str[i];
		if (str[i] != 'w' && str[i] != last)
			break;
		prevlen++;
	}
	max = prevlen;

	while (i < n) {
		nextlen = expand(str, i);
		prevlen += expand_head(str, i - prevlen);
		runningmax = nextlen - i + prevlen;
		if (runningmax > max)
			max = runningmax;
		prevlen = nextlen - i;
		i = nextlen;
	}

	if (max > n)
		fprintf(fout, "%d\n", n);
	
	fprintf(fout, "%d\n", max);
	free(str);
	exit(0);
}
