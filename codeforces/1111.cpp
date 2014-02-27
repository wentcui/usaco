#include <stdio.h>
#include <vector>

#include <string.h>

using namespace std;
int K, N, M;

vector<int> dfs(vector<int> *graph, vector<int> *connected, bool *visited, int curv) {
	int i;
	vector<int> res, subres;
	if (visited[curv])
		return connected[curv];

	visited[curv] = true;
	for(i = 0; i < graph[curv].size(); i++) {
		if (!visited[graph[curv][i]]) {
			subres = dfs(graph, connected, visited, graph[curv][i]);
			res.insert(res.end(), subres.begin(), subres.end());
		}
	}
	res.push_back(curv);
	connected[curv] = res;
	return res;
}

int main() {
	int cases, caseno = 0, i, j, v, f, t, count[1001], maxc;
	vector<int> people, vertex;
	vector<int> graph[1001], connected[1001];
	bool visited[1001];
	scanf("%d", &cases);
	while(cases--) {
		people.clear();
		vertex.clear();
		for(i = 1; i <= 1000; i++) {
			graph[i].clear();
			connected[i].clear();
		}
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
		for(i = 0; i < vertex.size(); i++) {
			if (!visited[vertex[i]])
				dfs(graph, connected, visited, vertex[i]);
		}
		for(i = 0, maxc = 0; i < people.size(); i++) {
			for(j = 0; j < connected[people[i]].size(); j++) {
				count[connected[people[i]][j]]++;
				if (count[connected[people[i]][j]] == people.size())
					maxc++;
			}
		}

		printf("Case %d: %d\n", ++caseno, maxc);
	}
	return 0;
}
