#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <queue>

using namespace std;

int n;
vector<int> graph[20001];
vector<int> vertex;
int result[20001];
int flags[20001];

int bfs(int v) {
	int g1 = 0, g2 = 0, i;
	queue <int> q;
	flags[v] = -1;
	g1++;
	q.push(v);
	while(!q.empty()) {
		v = q.front();
		q.pop();
		for(i = 0; i < graph[v].size(); i++) {
			if (flags[graph[v][i]])	continue;
			q.push(graph[v][i]);
			flags[graph[v][i]] = -flags[v];
			if (flags[v] < 0)
				g2++;
			else
				g1++;
		}
	}
	return max(g1, g2);
}

int fn(void) {
	int i, v, r = 0, sum = 0;
	for(i = 0; i < vertex.size(); i++) {
		v = vertex[i];
		if (flags[v])	continue;
		result[r++] = bfs(v);
	}
	for(i = 0; result[i] > 0; i++) {
		sum += result[i];
	}
	return sum;
}

int main() {
	int caseno = 0, cases;
	int i, f, t;
	scanf("%d", &cases);
	while(cases--) {
		memset(result, 0, sizeof(int) * 20001);
		memset(flags, 0, sizeof(int) * 20001);
		for(i = 0; i < 20001; i++) {
			graph[i].clear();
		}
		vertex.clear();
		scanf("%d", &n);
		for(i = 1; i <= n; i++) {
			scanf("%d %d", &f, &t);
			graph[f].push_back(t);
			graph[t].push_back(f);
			if (!flags[f]) {
				vertex.push_back(f);
				flags[f] = 1;
			}

			if (!flags[t]) {
				vertex.push_back(t);
				flags[t] = 1;
			}
		}
		memset(flags, 0, sizeof(int) * 20001);
		printf("Case %d: %d\n", ++caseno, fn());
	}
}
