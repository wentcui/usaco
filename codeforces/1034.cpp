#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <vector>

using namespace std;

int N, M;
int dfn[10001], low[10001], belong[10001];
int step, group;
vector<int> graph[10001];
stack<int> st;

void tarjan(int u) {
	int v;
	dfn[u] = low[u] = step++;
	st.push(u);
	for(int i = 0; i < graph[u].size(); i++) {
		v = graph[u][i];
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (!belong[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		do {
			v = st.top();
			st.pop();
			belong[v] = group;
		} while (v != u);
		group++;
	}
}

int get_nr() {
	int ret = group - 1, cg, vg, v;
	int temp[10001];
	memset(temp, 0, sizeof(int) * 10001);
	for(int i = 1; i <= N; i++) {
		cg = belong[i];
		for(int j = 0; j < graph[i].size(); j++) {
			v = graph[i][j];
			vg = belong[v];
			if (vg == cg)	continue;
			if (!temp[vg])
				ret--;
			temp[vg]++;
		}
	}
	return ret;
}

int main() {
	int cases, caseno = 0;
	int f, t;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &N, &M);

		step = group = 1;
		memset(dfn, 0, sizeof(int) * 10001);
		memset(low, 0, sizeof(int) * 10001);
		memset(belong, 0, sizeof(int) * 10001);
		for(int i = 1; i <= M; i++) {
			scanf("%d %d", &f, &t);
			graph[f].push_back(t);
		}
		for(int i = 1; i <= N; i++) {
			if (!belong[i])
				tarjan(i);
		}
		printf("Case %d: %d\n", ++caseno, get_nr());
		for(int i = 0; i <= N; i++) {
			graph[i].clear();
		}
	}
	return 0;
}
