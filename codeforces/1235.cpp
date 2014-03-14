#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <queue>

#define MAX 1000000000
using namespace std;

int N, K, cindex;
unsigned int left[20000] = {0}, right[20000] = {0};

int cmp(const void *a,const void *b) {
	unsigned int *x = (unsigned int *) a;
	unsigned int *y = (unsigned int *) b;
	return *x - *y;
}

void gen(unsigned int *candidates, unsigned int sum, unsigned int *arr, int curindex, int len) {
	if (curindex >= len) {
		candidates[cindex++] = sum;
		return;
	}

	gen(candidates, sum, arr, curindex + 1, len);
	gen(candidates, sum + arr[curindex], arr, curindex + 1, len);
	gen(candidates, sum + 2 * arr[curindex], arr, curindex + 1, len);
}


int bSearch(unsigned int *arr, int start, int len, unsigned int value) {
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
	int ll, rl, rt, i, cases, caseno = 0;
	unsigned int input[20] = {0};
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &N, &K);
		memset(input, 0, sizeof(unsigned int) * 20);
		for(i = 0; i < N; i++) {
			scanf("%d", &input[i]);
		}
		cindex = 0;
		memset(left, 0, sizeof(unsigned int) * 20000);
		memset(right, 0, sizeof(unsigned int) * 20000);
		gen(left, 0, input, 0, N / 2);
		ll = cindex;
		qsort(left, ll, sizeof(unsigned int), cmp);


		cindex = 0;
		gen(right, 0, input + N / 2, 0, N - N / 2);
		rl = cindex;
		qsort(right, rl, sizeof(unsigned int), cmp);

		for(i = 0; i < ll; i++) {
			rt = bSearch(right, 0, rl, K - left[i]);
			if (right[rt] == K - left[i]) {
				printf("Case %d: Yes\n", ++caseno);
				break;
			}
		}
		if (i == ll)
			printf("Case %d: No\n", ++caseno);
			
	}
	return 0;
}
