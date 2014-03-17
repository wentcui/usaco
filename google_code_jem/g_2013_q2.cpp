#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

#define PP pair<pair<int, int>, int>
using namespace std;

int N, M;

struct cmp {
	bool operator() (const PP &p1, const PP &p2) {
		return p1.second > p2.second;
	}
};

bool validate(int input[101][101], PP p, bool verified[2][101]) {
	int i, x = p.first.first, y = p.first.second;
	bool r1 = true, r2 = true;
	printf("%d, %d: %d\n", p.first.first, p.first.second, p.second);
	if (!verified[0][x]) {
		for(i = 1; i <= N; i++)
			if (input[i][y] > input[x][y]) {
				r1 = false;
				break;
			}
		verified[0][x] = true;
	}
	if (!verified[1][y]) {
		for(i = 1; i <= M; i++)
			if (input[x][i] > input[x][y]) {
				r2 = false;
				break;
			}
		verified[1][y] = true;
	}
	if (r1 || r2)
		printf("ret true\n");
	else
		printf("ret false\n");
	return (r1 || r2);
}

int main() {
	FILE* fin = fopen("q2.in", "r");
	FILE* fout = fopen("q2.out", "w");
	int cases, caseno = 0, i, j;
	int input[101][101];

	fscanf(fin, "%d", &cases);
	while(cases--) {
		priority_queue<PP, vector<PP>, cmp> q;
		bool verified[2][101] = {{false}}, s = true;
		fscanf(fin, "%d %d", &N, &M);
		for(i = 1; i <= N; i++) {
			for(j = 1; j <= M; j++) {
				fscanf(fin, "%d", &input[i][j]);
				q.push(make_pair(make_pair(i, j), input[i][j]));
			}
		}

		while(!q.empty()) {
			PP p = q.top();
			q.pop();
			if(!validate(input, p, verified)) {
				s = false;
				fprintf(fout, "Case #%d: No\n", ++caseno);
				break;
			}
		}

		if (s)
			fprintf(fout, "Case #%d: Yes\n", ++caseno);
	}
}
