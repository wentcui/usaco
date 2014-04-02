#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
	return a > b ? b : a;
}

int main() {
	int cases, caseno = 0;
	int r, n, min_v;
	int a, b, c, na, nb, nc;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);

		a = b = c = na = nb = nc = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &r);
			na = min(b, c) + r;
			
			scanf("%d", &r);
			nb = min(a, c) + r;

			scanf("%d", &r);
			nc = min(a, b) + r;

			a = na, b = nb, c = nc;
		}
		a = min(a, b);
		a = min(a, c);

		printf("Case %d: %d\n", ++caseno, a);
	}
	return 0;
}
