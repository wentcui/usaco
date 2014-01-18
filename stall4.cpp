/*
ID: wentcui1
LANG: C++
TASK: stall4
*/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <utility>
#include <queue>

#define PP pair<pair<int, int>, int>
#define ITF 200
#define LEN 405

using namespace std;

struct cmp {
    bool operator() (const PP &p1, const PP &p2) {
        return p2.second > p1.second;
    }
};


int main() {
	FILE *fin = fopen("stall4.in", "r");
	FILE *fout = fopen("stall4.out", "w");
	int i, j, k, f, t, v, maxflow = 0;
	int b1 = 1, b2;
	int N, M, s;
	int dist[LEN][LEN], prev[LEN], flow[LEN], visited[LEN];
	fscanf(fin, "%d %d", &N, &M);
	b2 = N + b1;
	vector<int> graph[LEN];
	for(i = 0; i < LEN; i++)
		for(j = 0; j < LEN; j++)
			dist[i][j] = 0;
	for(i = 1; i <= N; i++) {
		f = i;
		fscanf(fin, "%d", &s);
		for(j = 1; j <= s; j++) {
			fscanf(fin, "%d", &t);
			dist[f + b1][t + b2] = 1;
			graph[f + b1].push_back(t + b2);
			graph[t + b2].push_back(f + b1);
		}
	}
	fclose(fin);
	for(i = 2; i <= N + 1; i++) {
		dist[1][i] = 1;
		graph[1].push_back(i);
		graph[i].push_back(1);
	}
	for(i = N + 2; i <= N + M + 1; i++) {
		dist[i][N + M + 2] = 1;
		graph[i].push_back(N + M + 2);
		graph[N + M + 2].push_back(i);
	}

	while(1) {
		priority_queue<PP, vector<PP>, cmp> q;
		q.push(make_pair(make_pair(1, 1), ITF));
		memset(prev, 0, sizeof(int) * LEN);
		memset(visited, 0, sizeof(int) * LEN);
		memset(flow, ITF, sizeof(int) * LEN);
		for(i = 1; i <= N + M + 2 && !q.empty(); i++) {
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
			if (top.first.second == N + M + 2)
				break;

			for(j = 0; j < graph[top.first.second].size(); j++) {
				int next = graph[top.first.second][j];
				if (visited[next] || dist[top.first.second][next] <= 0) continue;
				//printf("next: %d, flow: %d\n", next, min(flow[top.first.second], dist[top.first.second][next]));
				q.push(make_pair(make_pair(top.first.second, next), min(flow[top.first.second], dist[top.first.second][next])));
			}
		}
		if (!prev[N + M + 2])
			break;
		maxflow += flow[N + M + 2];

		prev[1] = -1;
		int pr = prev[N + M + 2];
		int cr = N + M + 2;
		while(pr > 0) {
			dist[pr][cr] -= flow[N + M + 2];
			dist[cr][pr] += flow[N + M + 2];
			//printf("pr: %d, cr: %d, f: %d, o: %d, r: %d\n", pr, cr, flow[N + M + 2], dist[pr][cr], dist[cr][pr]);
			cr = pr;
			pr = prev[cr];
		}
	}
	fprintf(fout, "%d\n", maxflow);
	fclose(fout);
	return 0;
}

