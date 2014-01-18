/*
ID: wentcui1
LANG: C++
TASK: ditch
*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <utility>
#include <queue>

#define PP pair<pair<int, int>, int>
#define ITF 20000000
#define LEN 205

using namespace std;

struct cmp {
    bool operator() (const PP &p1, const PP &p2) {
        return p2.second > p1.second;
    }
};


int main() {
	FILE *fin = fopen("ditch.in", "r");
	FILE *fout = fopen("ditch.out", "w");
	int i, j, k, f, t, v, maxflow = 0;
	int N, M;
	fscanf(fin, "%d %d", &N, &M);
	int dist[LEN][LEN], prev[LEN], flow[LEN], visited[LEN];
	vector<int> graph[LEN];
	for(i = 0; i < LEN; i++)
		for(j = 0; j < LEN; j++)
			dist[i][j] = 0;
	for(i = 1; i <= N; i++) {
		fscanf(fin, "%d %d %d", &f, &t, &v);
		dist[f][t] += v;
		graph[f].push_back(t);
		graph[t].push_back(f);
	}
	fclose(fin);

	while(1) {
		priority_queue<PP, vector<PP>, cmp> q;
		q.push(make_pair(make_pair(1, 1), ITF));
		memset(prev, 0, sizeof(int) * LEN);
		memset(visited, 0, sizeof(int) * LEN);
		memset(flow, ITF, sizeof(int) * LEN);
		for(i = 1; i <= M && !q.empty(); i++) {
			PP top = q.top();
			q.pop();
			//printf("cur: %d, flow: %d\n", top.first.second, top.second);
			if (visited[top.first.second]) {
				i--;
				continue;
			}
			flow[top.first.second] = top.second;
			prev[top.first.second] = top.first.first;
			visited[top.first.second] = 1;
			if (top.first.second == M)
				break;

			for(j = 0; j < graph[top.first.second].size(); j++) {
				int next = graph[top.first.second][j];
				if (visited[next] || dist[top.first.second][next] <= 0) continue;
				//printf("next: %d, flow: %d\n", next, min(flow[top.first.second], dist[top.first.second][next]));
				q.push(make_pair(make_pair(top.first.second, next), min(flow[top.first.second], dist[top.first.second][next])));
			}
		}
		if (!prev[M])
			break;
		maxflow += flow[M];

		prev[1] = -1;
		int pr = prev[M];
		int cr = M;
		while(pr > 0) {
			dist[pr][cr] -= flow[M];
			dist[cr][pr] += flow[M];
			//printf("pr: %d, cr: %d, f: %d, o: %d, r: %d\n", pr, cr, flow[M], dist[pr][cr], dist[cr][pr]);
			cr = pr;
			pr = prev[cr];
		}
	}
	fprintf(fout, "%d\n", maxflow);
	fclose(fout);
	return 0;
}

