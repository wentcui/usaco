#include <stdio.h>
#include <vector>

using namespace std;
int K, N, M;

vertex<int> dfs(vector<int> graph, vector<int> connected, bool *visited, int curv) {
	int i;
	vector<int> res, subres, ret;
	if (visited[curv])
		return connected[curv];

	visited[curv] = true;
	for(i = 0; i < graph[curv].size(); i++) {
		if (!visited[graph[curv][i]]) {
			subres = dfs(graph, connected, visited, graph[curv][i]);
			res.insert(res.end(), subres.begin(), subres.end());
		}
	}
	connected[curv] = res;
	ret.push_back(curv);
	ret.insert(ret.end(), res.begin(), res.end());
	return ret;
}

int main() {
	int cases, caseno = 0, i, j, v, f, t, count[1001], maxv, maxc;
	vector<int> people, vertex;
	vector<int> graph[1001], connected[1001];
	bool visited[1001];
	scanf("%d", &cases);
	while(cases--) {
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
		for(i = 0; i <= vertex.size(); i++) {
			if (!visited[vertex[i]])
				dfs(graph, connected, visited, vertex[i]);
		}
		for(i = 0, maxv = -1, maxc = 0; i < people.size(); i++) {
			for(j = 0; j < connected[people[i]].size(); j++) {
				count[connected[people[i]][j]]++;
				if (count[connected[people[i]][j]] > maxv) {
					maxv = count[connected[people[i]][j]];
					maxc = 1;
				} else
					maxc++;
			}
		}

		printf("Case %d: %d\n", maxc);
	}
	return 0;
}
