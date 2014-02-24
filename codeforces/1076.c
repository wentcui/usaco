#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N, M;

int judge(int *input, int key) {
	int i, j, sum, count;
	for(i = 1, count = 0; i <= N;) {
		if (input[i] > key)
			return 0;
		for(j = i, sum = 0; j <= N; j++) {
			if (sum + input[j] <= key)
				sum += input[j];
			else
				break;
		}
		i = j;
		count++;
	}
	if (count <= M)
		return 1;
	return 0;
}

int main() {
	int cases, caseno = 0;
	int sum, input[1001];
	int i, j, l, r, mid;
	scanf("%d", &cases);
	while(cases--) {	
		scanf("%d %d", &N, &M);
		sum = 0;
		for(i = 1; i <= N; i++) {
			scanf("%d", &input[i]);
			sum += input[i];
		}
		l = 0;
		r = sum;
		while(l < r) {
			mid = l + (r - l) / 2;
			if (judge(input, mid))
				r = mid;
			else
				l = mid + 1;
		}
		printf("Case %d: %d\n", ++caseno, l);
	}
	return 0;
}
