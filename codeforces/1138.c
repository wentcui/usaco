#include <stdio.h>
#include <stdlib.h>

int get_zero_nr(int n) {
	int count = 0;
	while(n > 0) {
		count += (n / 5);
		n /= 5;
	}
	return count;
}

int fun(int count) {
	int l = 1, r = 5 * count, mid;
	while(l < r) {
		mid = l + (r - l) / 2;
		if (get_zero_nr(mid) < count)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}

int main() {
	int cases, caseno = 0, Q, ret;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &Q);
		ret = fun(Q);
		if (get_zero_nr(ret) == Q)
			printf("Case %d: %d\n", ++caseno, ret);
		else
			printf("Case %d: impossible\n", ++caseno);
	}
	return 0;
}
