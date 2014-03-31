#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>

#define PP pair<pair<int, int>, int>
#define MAX_V 2000000000

using namespace std;

struct cmp {
	bool operator() (const PP &p1, const PP &p2) {
		return p1.second > p2.second;
	}
};

void dijkstra(vector<pair<int, int> > *graph, int *res, int start) {
	PP p;
	priority_queue<PP, vector<PP>, cmp> q;
	bool map[5001] = {false};
	map[start] = true;
	for(int i = 0; i < graph[start].size(); i++)
		q.push(make_pair(make_pair(start, graph[start][i].first), graph[start][i].second));

	while(!q.empty()) {
		p = q.top();
		q.pop();
		if (map[p.first.second])	continue;

		map[p.first.second] = true;
		res[p.first.second] = p.second;

		for(int i = 0; i < graph[p.first.second].size(); i++) {
			pair<int, int> nextp = graph[p.first.second][i];
			if (map[nextp.first])	continue;
			q.push(make_pair(make_pair(p.first.second, nextp.first), p.second + nextp.second));
		}
	}
}

int main() {
	int cases, caseno = 0;
	int N, R, f, t, d, d1, d2;
	scanf("%d", &cases);
	while(cases--) {
		vector<pair<int, int> > graph[5001];
		int ds[5001] = {0}, dd[5001] = {0}, min = MAX_V;
		vector<PP> es;
		scanf("%d %d", &N, &R);
		for(int i = 1; i <= R; i++) {
			scanf("%d %d %d", &f, &t, &d);
			graph[f].push_back(make_pair(t, d));
			graph[t].push_back(make_pair(f, d));
			es.push_back(make_pair(make_pair(f, t), d));
			es.push_back(make_pair(make_pair(t, f), d));
		}
		dijkstra(graph, ds, 1);
		dijkstra(graph, dd, N);
		d = ds[N];
		for(int i = 0; i < es.size(); i++) {
			PP p = es[i];
			d1 = ds[p.first.first] + dd[p.first.second] + p.second;
			d2 = ds[p.first.first] + dd[p.first.second] + 3 * p.second;
			if (d1 > d) {
				if (d1 < min)
					min = d1;
			}
			if (d2 > d) {
				if (d2 < min)
					min = d2;
			}
		}
		printf("Case %d: %d\n", ++caseno, min);
	}
	return 0;
}

