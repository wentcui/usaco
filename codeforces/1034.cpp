#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int get_head(int *id, int index) {
	int pid = 0;
	if (!id[index])
		return index;
	pid = get_head(id, id[index]);
	id[index] = pid;
	return pid;
}

int main() {
	int cases, caseno = 0;
	int N, M, id[10001], f, t, count, pid;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &N, &M);
		memset(id, 0, sizeof(int) * 10001);
		count = N;
		for(int i = 1; i <= M; i++) {
			scanf("%d %d", &f, &t);
			if (!id[t]) {
				pid = get_head(id, f);
				if (pid == t)
					continue;
				id[t] = f;
				count--;
			}
		}
		printf("Case %d: %d\n", ++caseno, count);
	}
}
