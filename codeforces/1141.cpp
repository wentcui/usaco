#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>

#define MAX 501
#define PP pair<int, int>

using namespace std;

bool pmap[MAX] = {true};
bool visited[MAX * 2] = {false};
vector<int> graph[1001];

void prime_map_gen() {
	int i, j;
	pmap[0] = false;
	pmap[1] = false;
	for(i = 2; i <= 500; i++) {
		if (!pmap[i])	continue;
		for(j = 2; j * i <= MAX; j++)
			pmap[i * j] = false;
	}
}

void get_list(int n, vector<int> &list) {
	//if (pmap[n])
	//	return;

	for(int i = 2; i <= n / 2; i++) {
		if (pmap[i] && !(n % i))
			list.push_back(i);
	}
}

int bfs(int f, int t) {
	int step;
	vector<int> l;
	queue<PP> q;
	q.push(make_pair(f, 0));
	while(!q.empty()) {
		f = q.front().first;
		step = q.front().second;
		q.pop();
		if (f == t)
			return step;
		if (graph[f].size() == 0)
			get_list(f, graph[f]);
		l = graph[f];
		for(int i = 0; i < l.size(); i++) {
			int next = l[i] + f;
			if (next <= t && !visited[next]) {
				visited[next] = true;
				q.push(make_pair(next, step + 1));
			}
		}
	}
	return -1;
}

int main() {
	int cases, caseno = 0, f, t;
	memset(pmap, true, sizeof(bool) * MAX);
	prime_map_gen();
	
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &f, &t);
		memset(visited, false, sizeof(bool) * 2 * MAX);
		printf("Case %d: %d\n", ++caseno, bfs(f, t));
	}
	return 0;
}
