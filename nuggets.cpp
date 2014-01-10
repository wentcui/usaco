/*
ID: wentcui1
LANG: C++
TASK: nuggets
*/

#include <stdio.h>
#include <map>

#define ITF 2000000000
#define MAX 300
using namespace std;
int n;

bool validate(map<int, bool> &mymap, int *values, int v) {
	int i;
	for(i = 1; i <= n; i++) {
		int oldv = v - values[i];
		if (oldv < 0)	continue;
		if (!oldv || mymap.find(oldv) == mymap.end()) return false;
	}
	return true;
}

int main() {
	FILE* fin = fopen("nuggets.in", "r");
	FILE* fout = fopen("nuggets.out", "w");
	int i = 0, runningmin = 0, runningindex = 0, max = 0, min = ITF;
	map<int, bool> mymap;
	int candidates[10000] = {0}, pos = 0;
	int values[300] = {0}, indexs[300] = {0};

	fscanf(fin, "%d", &n);
	for(i = 1; i <= n; i++) {
		fscanf(fin, "%d", &values[i]);
		if (values[i] < min)	min = values[i];
	}


	if (min == 1) {
		fprintf(fout, "0\n");
		return 0;
	}

	for (i = 1; i < min; i++) {
		mymap[i] = true;
		candidates[pos++] = i;
	}

	printf("start\n");

	while(runningmin < ITF) {
		runningmin = ITF;
		for(i = 1; i <= n; i++) {
			int next = candidates[indexs[i]] + values[i];

			if (mymap.find(next) != mymap.end()) {
				indexs[i]++;
				continue;
			}
			if (next < runningmin) {
				runningmin = next;
				runningindex = i;
			}
		}
		printf("runningmin: %d\n", runningmin);
		indexs[runningindex]++;
		if (runningmin < ITF && validate(mymap, values, runningmin)) {
			if (pos >= 10000) {
				printf("ERR\n");
				return 0;
			}
			candidates[pos++] = runningmin;
			mymap[runningmin] = true;

			printf("validated: %d\n", runningmin);

			min = runningmin;
		}
	}

	printf("%d\n", min);

	return 0;
}
