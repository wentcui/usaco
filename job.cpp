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
#define ITF 200000000

using namespace std;
int N, M1, M2;

struct cmp {
	bool operator() (const PP &p1, const PP &p2) {
		return p2.second > p1.second;
	}
};

int compare (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

int compare1 (const void * a, const void * b)
{
	return ( *(int*)b - *(int*)a );
}

void get_finish_time(int M, int machine[2][31], int *time, int &at) {
	int i, j, k;
	int left = N;
	int t = 0;
	for(i = 1; i <= M; i++) {
		machine[1][i] = machine[0][i];
		left--;
	}
	while(1) {
		priority_queue<PP, vector<PP>, cmp> q;
		vector<int> available;
		t++;

		for(i = 1; i <= M; i++) {
			if (machine[1][i] <= 1) {
				available.push_back(i);
				if (machine[1][i] == 1)
					time[t]++;
			}
			if (machine[1][i] > 0)
				machine[1][i]--;
			q.push(make_pair(i, machine[1][i]));
		}
		//fprintf(fout, "t: %d, v: %d\n", t, time[t]);
		if (available.size() == M && left <= 0)
			break;
		//fprintf(fout, "t: %ld, left: %d\n", available.size(), left);
		for(i = 0; i < available.size(); i++) {
			if (left > 0) {
				//machineA[1][available[i]] = machineA[0][available[i]];
				left--;
			} else if (!q.empty() && q.top().second > machine[0][available[i]]) {
				machine[1][q.top().first] = 0;
				q.pop();
			} else
				break;
			machine[1][available[i]] = machine[0][available[i]];
		}
	}
	at = t;
	return;
}

int main() {
	FILE *fin = fopen("job.in", "r");
	FILE *fout = fopen("job.out", "w");
	int i, j, k, left, tA = 0, tB = 0;
	int machineA[2][31], machineB[2][31], timeA[20001], timeB[20001];
	fscanf(fin, "%d %d %d", &N, &M1, &M2);
	memset(machineA[0], 0, sizeof(int) * 31);
	memset(machineA[1], 0, sizeof(int) * 31);
	memset(machineB[0], 0, sizeof(int) * 31);
	memset(machineB[1], 0, sizeof(int) * 31);
	memset(timeA, 0, sizeof(int) * 20001);
	memset(timeB, 0, sizeof(int) * 20001);
	
	for(i = 1; i <= M1; i++)
		fscanf(fin, "%d", &machineA[0][i]);
	for(i = 1; i <= M2; i++)
		fscanf(fin, "%d", &machineB[0][i]);
	fclose(fin);

	qsort(machineA[0], M1 + 1, sizeof(int), compare);
	qsort(machineB[0], M2 + 1, sizeof(int), compare);

	get_finish_time(M1, machineA, timeA, tA);
	for(i = 1; i <= tA; i++) {
		printf("%d ", timeA[i]);
	}
	printf("\ntA: %d\n", tA);
	get_finish_time(M2, machineB, timeB, tB);
	for(i = 1; i <= tB; i++) {
		printf("%d ", timeB[i]);
	}
	printf("\ntB: %d\n", tB);
	
	return 0;
}

