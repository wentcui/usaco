/*
ID: wentcui1
LANG: C++
TASK: butter
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

#define ITF 200000000

using namespace std;

int N, P, C;

int min(int a, int b) {
	return a > b ? b : a;
}

#define pp pair<int,int>

struct cmp {
	bool operator() (const pp &p1, const pp &p2) {
		return p1.second > p2.second;
	}
};


// return the sum of dist when choose p as center
int dij(int p, vector<pp> *dist, int *cInP) {
	int i, j, f, v;
	int sum = 0;
	int visited[801];
	memset(visited, 0, sizeof(int) * 801);
	vector<pp> dijres;
	pp toppair;
	priority_queue<pp, vector<pp>, cmp> q;

	q.push(make_pair(p, 0));
	for(i = 1; i <= P; i++) {
		toppair = q.top();
		q.pop();
		f = toppair.first;
		v = toppair.second;
		if (visited[f]) {
			i--;
			continue;
		}
		dijres.push_back(toppair);
		visited[f] = 1;

		for(j = 0; j < dist[f].size(); j++) {
			int pid = dist[f][j].first;
			int pdist = dist[f][j].second;
			if (visited[pid]) continue;
			q.push(make_pair(pid, v + pdist));
		}
	}

	for(i = 0; i < dijres.size(); i++) {
		f = dijres[i].first;
		v = dijres[i].second;
		sum += cInP[f] * v;
	}

	return sum;
}

main() {
	int cInP[801];
	FILE* fin = fopen("butter.in", "r");
	FILE* fout = fopen("butter.out", "w");
	int i, j, k, v, f, t;
	int mindist = ITF;
	memset(cInP, 0, sizeof(int) * 801);
	fscanf(fin, "%d %d %d", &N, &P, &C);
	vector<pp> dist[P + 1];

	for(i = 1; i <= N; i++) {
		fscanf(fin, "%d", &v);
		cInP[v]++;
	}


	for(i = 1; i <= C; i++) {
		fscanf(fin, "%d %d %d", &f, &t, &v);
		dist[f].push_back(make_pair(t, v));
		dist[t].push_back(make_pair(f, v));
	}

	for(i = 1; i <= P; i++) {
		int runningmin = dij(i, dist, cInP);
		if (runningmin < mindist)
			mindist = runningmin;
	}

	fprintf(fout, "%d\n", mindist);

	exit(0);
}
