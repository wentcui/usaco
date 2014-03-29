#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>

using namespace std;

int dfn[20001], low[20001], belong[20001];
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

int shrink(vector<int> *graph, int n) {
	vector<int> s_group[20001];
	int vg, cg, next, in_degree[20001] = {0};
	int in_c = 0, out_c = 0;
	for(int i = 1; i <= n; i++) {
		cg = belong[i];
		for(int j = 0; j < graph[i].size(); j++) {
			vg = belong[graph[i][j]];
			if (cg == vg)	continue;
			s_group[cg].push_back(vg);
		}
	}
	out_c = group - 1;
	for(int i = 1; i < group; i++) {
		if (s_group[i].size() > 0)
			out_c--;
		for(int j = 0; j < s_group[i].size(); j++)
			in_degree[s_group[i][j]]++;
	}
	for(int i = 1; i < group; i++) {
		if (!in_degree[i])
			in_c++;
	}
	return out_c > in_c ? out_c : in_c;
}

int main() {
	int cases, caseno = 0, N, K, f, t;
	scanf("%d", &cases);
	while(cases--) {
		vector<int> graph[20001];
		memset(dfn, 0, sizeof(int) * 20001);
		memset(low, 0, sizeof(int) * 20001);
		memset(belong, 0, sizeof(int) * 20001);
		step = group = 1;

		scanf("%d %d", &N, &K);
		for(int j = 1; j <= K; j++) {
			scanf("%d %d", &f, &t);
			graph[f].push_back(t);
		}
		for(int i = 1; i <= N; i++) {
			if (!belong[i])
				tarjan(graph, i);
		}
		if (group == 2)
			printf("Case %d: 0\n", ++caseno);
		else
			printf("Case %d: %d\n", ++caseno, shrink(graph, N));
	}
	return 0;
}
