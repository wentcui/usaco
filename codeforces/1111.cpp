#include <stdio.h>
#include <vector>

#include <string.h>

using namespace std;
int K, N, M;
bool map[1001][1001];

void dfs(vector<int> *graph, bool *visited, bool *visited_sg, int curv, int ori) {
	int i;
	visited[curv] = true;
	map[ori][curv] = true;
	if (visited_sg[curv]) {
		for(i = 1; i <= 1000; i++)
			map[ori][i] |= map[curv][i];
		return;
	}
	for(i = 0; i < graph[curv].size(); i++) {
		if (!visited[graph[curv][i]]) {
			dfs(graph, visited, visited_sg, graph[curv][i], ori);
		}
	}
}

int main() {
	int cases, caseno = 0, i, j, v, f, t, count[1001], maxc;
	vector<int> people, vertex;
	vector<int> graph[1001];
	bool visited[1001], visited_sg[1001];
	scanf("%d", &cases);
	while(cases--) {
		maxc = 0;
		people.clear();
		vertex.clear();
		for(i = 0; i <= 1000; i++) {
			graph[i].clear();
			memset(map[i], false, sizeof(bool) * 1001);
		}
		memset(visited_sg, false, sizeof(bool) * 1001);
		memset(visited, false, sizeof(bool) * 1001);
		memset(count, 0, sizeof(int) * 1001);
		scanf("%d %d %d", &K, &N, &M);
		for(i = 1; i <= K; i++) {
			scanf("%d", &v);
			people.push_back(v);
		}
		for(i = 1; i <= M; i++) {
			scanf("%d %d", &f, &t);
			graph[f].push_back(t);
			vertex.push_back(f);
		}
		if (!K || !N || !M) {
			printf("Case %d: 0\n", ++caseno);
			continue;
		}

		for(i = 0; i < people.size(); i++) {
			memset(visited, false, sizeof(bool) * 1001);
			dfs(graph, visited, visited_sg, people[i], people[i]);
			visited_sg[people[i]] = true;
			for(j = 1; j <= 1000; j++) {
				if (!map[people[i]][j]) continue;
				count[j]++;
				if (count[j] == people.size())
					maxc++;
			}
		}

		printf("Case %d: %d\n", ++caseno, maxc);
	}
	return 0;
}
