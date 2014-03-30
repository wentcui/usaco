#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>

using namespace std;

int dfn[1001], low[1001], belong[1001];
int step, group;
stack<int> st;

void tarjan(vector<int> *graph, int u) {
	int v;
	dfn[u] = low[u] = step++;
	st.push(u);

	for(int i = 0; i < graph[u].size(); i++) {
		v = graph[u][i];
		if (!dfn[v]) {
			tarjan(graph, v);
			low[u] = min(low[u], low[v]);
		} else if (!belong[v])
			low[u] = min(dfn[v], low[u]);
	}

	if (dfn[u] == low[u]) {
		do {
			v = st.top();
			st.pop();
			belong[v] = group;
		} while(u != v);
		group++;
	}
}

bool shrink(vector<int> *graph, vector<int> vs) {
	vector<int> s_group[1001];
	int v, vg, cg, next, count = group - 1, in_degree[1001] = {0}, start = -1;
	bool e_map[1001][1001] = {{false}};
	for(int i = 0; i < vs.size(); i++) {
		int v = vs[i];
		cg = belong[v];
		for(int j = 0; j < graph[v].size(); j++) {
			vg = belong[graph[v][j]];
			if (cg == vg)	continue;
			if (e_map[cg][vg])	return false;
			e_map[cg][vg] = true;
			s_group[cg].push_back(vg);
		}
	}
	for(v = 1; v < group; v++) {
		if (s_group[v].size() > 1)
			return false;
		if (!s_group[v].size())
			continue;
		next = s_group[v][0];
		in_degree[next]++;
		if (in_degree[next] > 1)
			return false;
	}
	for(v = 1; v < group; v++) {
		if (in_degree[v])	continue;
		if (start < 0)
			start = v;
		else
			return false;
	}
	while(true) {
		if (s_group[start].size() > 1) {
			return false;
		}
		count--;
		if (s_group[start].size() == 0)
			break;
		start = s_group[start][0];
	}
	if (count)
		return false;
	return true;
}

int main() {
	int cases, caseno = 0, N, K, f, t;
	scanf("%d", &cases);
	while(cases--) {
		bool v_map[1001] = {false}, failed = false;
		vector<int> graph[1001], vs;
		memset(dfn, 0, sizeof(int) * 1001);
		memset(low, 0, sizeof(int) * 1001);
		memset(belong, 0, sizeof(int) * 1001);
		step = group = 1;

		scanf("%d", &N);
		for(int i = 1; i <= N; i++) {
			scanf("%d", &K);
			for(int j = 1; j <= K; j++) {
				scanf("%d %d", &f, &t);
				graph[f].push_back(t);
				if (!v_map[f]) {
					v_map[f] = true;
					vs.push_back(f);
				}
				if (!v_map[t]) {
					v_map[t] = true;
					vs.push_back(t);
				}
			}
		}
		tarjan(graph, 0);
		for(int i = 0; i < vs.size(); i++) {
			if (!belong[vs[i]]) {
				failed = true;
				break;
			}
		}
	
		if (failed || !shrink(graph, vs))
			printf("Case %d: NO\n", ++caseno);
		else
			printf("Case %d: YES\n", ++caseno);
	}
	return 0;
}
