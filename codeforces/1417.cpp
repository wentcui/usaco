#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

int visited[50001];
int graph[50001];
int entry_p;
vector<int> loop;
bool inloop;

void dfs(int *graph, int id) {
	int next = 0;
	if (!id)
		return;
	if (visited[id] == -1) {
		inloop = true;
		entry_p = id;
		return;
	}
	if (visited[id])
		return;
	visited[id] = -1;
	next = graph[id];
	dfs(graph, next);
	if (visited[next] == -1)
		visited[id] = 1;
	else
		visited[id] = 1 + visited[next];

	if (id == entry_p) {
		for(int i = 0; i < loop.size(); i++) {
			visited[loop[i]] = visited[id];
		}

		inloop = false;
		loop.clear();
		entry_p = -1;
		return;
	}
	if (inloop)
		loop.push_back(id);
}

int main() {
	int cases, caseno = 0, f, t, N;
	int max_nr, max_id, ret;
	scanf("%d", &cases);
	while(cases--) {
		memset(graph, 0, sizeof(graph));
		memset(visited, 0, sizeof(visited));
		inloop = false;
		entry_p = -1;
		max_nr = max_id = 0;
		scanf("%d", &N);
		for(int i = 1; i <= N; i++) {
			scanf("%d %d", &f, &t);
			graph[f] = t;
		}
		for(int i = 1; i <= N; i++) {
			if (visited[i])	continue;
			dfs(graph, i);
			if (visited[i] > max_nr) {
				max_nr = visited[i];
				max_id = i;
			}
		}
		printf("Case %d: %d\n", ++caseno, max_id);
	}
	return 0;
}
