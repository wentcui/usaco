/*
ID: wentcui1
TASK: job
LANG: C++
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>

#define PP pair<int, int>

using namespace std;

struct cmp {
	bool operator() (const PP &p1, const PP &p2) {
		return p2.second > p1.second;
	}
};

int compare (const void * a, const void * b)
{
	  return ( *(int*)a - *(int*)b );
}

int main() {
	FILE *fin = fopen("job.in", "r");
	FILE *fout = fopen("job.out", "w");
	int N, M1, M2;
	int i, j, k, left, t = 0;
	int machineA[2][31], machineB[2][31], time[20001];
	fscanf(fin, "%d %d %d", &N, &M1, &M2);
	for(i = 1; i <= M1; i++)
		fscanf(fin, "%d", &machineA[0][i]);
	for(i = 1; i <= M2; i++)
		fscanf(fin, "%d", &machineB[0][i]);
	fclose(fin);
	qsort(machineA[0], M1, sizeof(int), compare);
	qsort(machineB[0], M2, sizeof(int), compare);
	left = N;
	for(i = 1; i <= M1; i++) {
		machineA[1][i] = machineA[0][i];
		left--;
	}
	while(1) {
		priority_queue<PP, vector<PP>, cmp> q;
		vector<int> available;
		t++;
		for(i = 1; i <= M1; i++) {
			if (machineA[1][i] <= 1) {
				available.push_back(i);
				if (machineA[1][i] == 1) {
					time[t]++;
				}
			} else
				q.push(make_pair(i, machineA[1][i]));

			if (machineA[1][i] > 0)
				machineA[1][i]--;
		}
		if (available.size() == M1 && left <= 0)
			break;
		for(i = 0; i < available.size(); i++) {
			printf("aaa\n");
			if (left > 0) {
				left--;
			} else if (q.top().second > machineA[0][available[i]]) {
				machineA[1][q.top().first] = 0;
				q.pop();
			} else
				break;
			machineA[1][available[i]] = machineA[0][available[i]];
		}
	}
	printf("%d\n", t);
/*
	for(i = 1; i <= t; i++) {
		printf("%d ", time[i]);
	}
	printf("\n");

	int at = 0;
	left = N; // number of tasks that didn't put into machines
	for(t = 1, at = 1; !time[t]; t++, at++);

	i = 1;
	printf("%d, %d, %d\n", t, at, time[t]);
	while (time[t] > 0 && i <= M2) {
		printf("%d\n", i);
		machineB[1][i] = machineB[0][i];
		time[t]--;
		left--;
		i++;
	}

	while (1) {
		at++;
		priority_queue<PP, vector<PP>, cmp> q;
		vector<int> available;
		
		for (i = 1; i <= M2; i++) {
			if (machineB[1][i] > 0)
				machineB[1][i]--;

			if (machineB[1][i])
				q.push(make_pair(i, machineB[1][i]));
			else
				available.push_back(i);
		}
		if (available.size() == M2 && left <= 0)
			break;
		while(t < 20001 && !time[t] && t < at)
			t++;
		for(i = 0; i < available.size(); i++) {
			if (time[t] > 0) {
				time[t]--;
				left--;
			} else if (q.top().second > machineB[0][available[i]]) {
				machineB[1][q.top().first] = 0;
				q.pop();
			} else
				break;
			machineB[1][available[i]] = machineB[0][available[i]];
		}
	}
	printf("final: %d\n", at);
	return 0;
*/
	return 0;
}






