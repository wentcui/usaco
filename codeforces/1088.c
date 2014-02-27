#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N, Q;

int bSearch(int *arr, int start, int len, int value) {
	int mid, l = start, r = len;
	while(l < r) {
		mid = l + (r - l) / 2;
		if (arr[mid] < value)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}

int main() {
	int cases, caseno = 0, i, s, e, ss, ee;
	int input[100001];
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &N, &Q);
		for(i = 1; i <= N; i++)
			scanf("%d", &input[i]);
		printf("Case %d:\n", ++caseno);
		for(i = 1; i <= Q; i++) {
			scanf("%d%d", &s, &e);
			ss = s;
			ee = e;
			s = bSearch(input, 1, N + 1, s);
			e = bSearch(input, s, N + 1, e);
			if (e <= N && input[e] == ee)
				e++;
			printf("%d\n", e - s);
		}
	}
	return 0;
}
