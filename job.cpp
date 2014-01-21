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
int compare1 (const void * a, const void * b)
{
	return ( *(int*)b - *(int*)a );
}

int main() {
	FILE *fin = fopen("job.in", "r");
	FILE *fout = fopen("job.out", "w");
	int N, M1, M2;
	int i, j, k, left, t = 0;
	int machineA[2][31], machineB[2][31], time[20001];
	fscanf(fin, "%d %d %d", &N, &M1, &M2);
	memset(machineA[0], 0, sizeof(int) * 31);
	memset(machineA[1], 0, sizeof(int) * 31);
	memset(machineB[0], 0, sizeof(int) * 31);
	memset(machineB[1], 0, sizeof(int) * 31);
	for(i = 1; i <= M1; i++)
		fscanf(fin, "%d", &machineA[0][i]);
	for(i = 1; i <= M2; i++)
		fscanf(fin, "%d", &machineB[0][i]);
	fclose(fin);

	for(i = 1; i <= M1; i++)
		printf("@%d", machineA[0][i]);
	for(i = 1; i <= M2; i++)
		printf("@%d", machineB[0][i]);
	printf("\n");
	qsort(machineA[0], M1, sizeof(int), compare);
	//qsort(machineB[0], M2, sizeof(int), compare1);
	for(i = 1; i <= M1; i++)
		printf("@%d", machineA[0][i]);
	for(i = 1; i <= M2; i++)
		printf("@%d", machineB[0][i]);
	printf("\n");
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
				if (machineA[1][i] == 1)
					time[t]++;
			}
			if (machineA[1][i] > 0)
				machineA[1][i]--;
			q.push(make_pair(i, machineA[1][i]));
		}
		//fprintf(fout, "t: %d, v: %d\n", t, time[t]);
		if (available.size() == M1 && left <= 0)
			break;
		//fprintf(fout, "t: %ld, left: %d\n", available.size(), left);
		for(i = 0; i < available.size(); i++) {
			if (left > 0) {
				//machineA[1][available[i]] = machineA[0][available[i]];
				left--;
			} else if (!q.empty() && q.top().second > machineA[0][available[i]]) {
				machineA[1][q.top().first] = 0;
				q.pop();
			} else
				break;
			machineA[1][available[i]] = machineA[0][available[i]];
		}
	}
	/*
	memset(time, 0, sizeof(int) * 20001);
	time[1] = 2;
	time[2] = 2;
	time[3] = 1;
	time[4] = 0;
	time[5] = 0;
	t = 3;*/
	printf("&&%d \n", t);
	for(i = 1; i <= t; i++) {
		printf("%d ", time[i]);
	}
	printf("\nend\n");
	int at = 0;
	left = N; // number of tasks that didn't put into machines
	for(t = 1, at = 1; !time[t]; t++, at++);
	printf("&&ttt%d \n", t);
	for(i = 1; i <= M1; i++)
		printf("@%d", machineA[0][i]);
	for(i = 1; i <= M2; i++)
		printf("@%d", machineB[0][i]);
	printf("\n");

	i = 1;
	//fprintf(fout, "%d, %d, %d\n", t, at, time[t]);
	while (time[t] > 0 && i <= M2) {
		machineB[1][i] = machineB[0][i];
		printf("%d v: %d   ", i, machineB[1][i]);
		time[t]--;
		left--;
		i++;
	}
	//fprintf(fout, "\n");
	while (1) {
		at++;
		vector<int> available;
		//long ss = available.size();
		//printf("a size: %ld\n", available.size());
		for(j = 1; j <= M2; j++) {
			printf("a: %d %d *", machineB[0][j], machineB[1][j]);
		}

		for (i = 1; i <= M2; i++) {
			if (machineB[1][i] > 0)
				machineB[1][i]--;

			if (!machineB[1][i])
				available.push_back(i);
		}
		printf("\n");
		for(j = 1; j <= M2; j++) {
			printf("b: %d %d *", machineB[0][j], machineB[1][j]);
		}
		printf("\n");
		//printf("left: %d, ll: %d\n", left, ll);
		if (left <= 0)
			break;
		while(t < 20001 && !time[t] && t < at)
			t++;
		//printf("curr t: %d, v: %d\n", t, time[t]);
		for(i = 0; i < available.size() && time[t] > 0; i++) {
			time[t]--;
			left--;
			machineB[1][available[i]] = machineB[0][available[i]];
		}
	}

	while(1) {
		at++;
		priority_queue<PP, vector<PP>, cmp> q;
		vector<int> available;
		//long ss = available.size();
		//printf("a size: %ld\n", available.size());

		for (i = M2; i > 0; i--) {
			if (machineB[1][i] > 0)
				machineB[1][i]--;

			if (machineB[1][i])
				q.push(make_pair(i, machineB[1][i]));
			else {
				available.push_back(i);
			}
		}
		printf("\n");
		for(j = 1; j <= M2; j++) {
			printf("%d %d ^", machineB[0][j], machineB[1][j]);
		}
		printf("\n");
		//printf("left: %d, ll: %d\n", left, ll);
		if (available.size() == M2)
			break;
		//printf("curr t: %d, v: %d\n", t, time[t]);
		for(i = 0; i < available.size(); i++) {
			if (!q.empty() && q.top().second > machineB[0][available[i]]) {
				machineB[1][q.top().first] = 0;
				q.pop();
				machineB[1][available[i]] = machineB[0][available[i]];
			} else
				break;
		}
	}


	fprintf(fout, "%d\n", at);
	fclose(fout);
	return 0;
}






