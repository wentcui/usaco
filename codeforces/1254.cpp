#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_V 2000000000
#define PP pair<int, int>

using namespace std;

struct cmp {
	bool operator() (const PP &p1, const PP &p2) {
		return p1.second > p2.second;
	}
};


int query(vector<PP> graph[101], int price[101], int c, int s, int t) {
	int dp[101][101] = {{0}}, min_v = MAX_V, next, v;
	vector<int> candi;
	PP p;
	bool vmap[101] = {false};
	for(int i = 0; i < 101; i++)
		memset(dp[0], 0x7f, sizeof(int) * 101);

	priority_queue<PP, vector<PP>, cmp> q;

	for(int i = 1; i <= c; i++)
		dp[s][i] = i * price[i];
	q.push(make_pair(s, 0));
	while(!q.empty()) {
		p = q.top();
		q.pop();
		if (p.first == t)
			return p.second;
		if (vmap[p.first])	continue;
		vmap[p.first] = true;
		for(int i = 0; i < graph[p.first].size(); i++) {
			next = graph[p.first][i];
			for(int j = 0; j <= c; j++) {
				for(int k = p.second; k - p.second <= j; k++)
					dp[next][j] = min(dp[next][j], dp[p.first][k] + (j - k + p.second) * price[next]);
				if (j == 0)
					q.push(make_pair(next, dp[next][0]));
			}
		}
	}
	return -1;
	/*
	   while(true) {
	   for(int i = 0; i < candi.size(); i++) {
	   v = candi[i];
	   for(int j = 0; j < graph[v].size(); j++) {
	   p = graph[v][j];
	   if (vmap[p.first])	continue;
	   for(int k = 0; k <= c; k++) { // k: the gas unit left in p.first
	   min_v = MAX_V;
	   for(int l = p.second; l <= c && l - p.second <= k; l++)
	   min_v = min(min_v, dp[v][l] + price[p.first] * (k - l + p.second));
	   dp[p.first][k] = min_v;
	   }
	   }
	   }
	   }*/
}

int main() {
	int cases, caseno = 0, ret;
	int N, M, price[101], f, t, v, q, c, s, t;
	while(cases--) {
		vector<PP> graph[101];
		scanf("%d %d", &N, &M);
		for(int i = 0; i < N; i++)
			scanf("%d", &price[i]);
		for(int i = 1; i <= M; i++) {
			scanf("%d %d %d", &f, &t, &v);
			graph[f].push_back(make_pair(t, v));
			graph[t].push_back(make_pair(f, v));
		}
		printf("Case %d:\n", ++caseno);
		scanf("%d", &q);
		for(int i = 1; i <= q; i++) {
			scanf("%d %d %d", &c, &s, &t);
			ret = query(graph, c, s, t);
			if (ret < 0)
				printf("impossible\n");
			else
				printf("%d\n", ret);
		}
	}
}
