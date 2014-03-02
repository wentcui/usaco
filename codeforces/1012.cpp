#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

int W, H;

bool validate(char map[21][21], bool visited[21][21], int x, int y) {
	if (x <= 0 || x > H)
		return false;
	if (y <= 0 || y > W)
		return false;
	if (visited[x][y] || map[x][y] == '#')
		return false;
	visited[x][y] = true;
	return true;
}

int fun(char map[21][21], int sx, int sy) {
	int count = 1, i, j;
	queue<int> qx, qy;
	bool visited[21][21] = {{false}};
	qx.push(sx);
	qy.push(sy);
	visited[sx][sy] = true;
	while(!qx.empty()) {
		sx = qx.front();
		sy = qy.front();
		qx.pop();
		qy.pop();
		if (validate(map, visited, sx - 1, sy)) {
			count++;
			qx.push(sx - 1);
			qy.push(sy);
		}

		if (validate(map, visited, sx, sy + 1)) {
			count++;
			qx.push(sx);
			qy.push(sy + 1);
		}

		if (validate(map, visited, sx, sy - 1)) {
			count++;
			qx.push(sx);
			qy.push(sy - 1);
		}

		if (validate(map, visited, sx + 1, sy)) {
			count++;
			qx.push(sx + 1);
			qy.push(sy);
		}
	}
	return count;
}

int main() {
	int cases, caseno = 0;
	int i, j, sx, sy;
	scanf("%d", &cases);
	while(cases--) {
		char map[21][21];
		scanf("%d %d", &W, &H);
		getchar();
		for(i = 1; i <= H; i++) {
			for(j = 1; j <= W; j++) {
				scanf("%c", &map[i][j]);
				if (map[i][j] == '@') {
					sx = i;
					sy = j;
				}
			}
			getchar();
		}
		printf("Case %d: %d\n", ++caseno, fun(map, sx, sy));
	}
}
