#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <queue>

#define MAX 1000000000
using namespace std;

int N, K;

int cmp(const void *a,const void *b) {
	int *x = (int *) a;
	int *y = (int *) b;
	return *x - *y;
}

bool fn(unsigned int *input) {
	unsigned long last;
	unsigned int lasttop, nexttop;
	vector<unsigned int> candidates;
	priority_queue <unsigned int> q;
	last = 0;
	candidates.push_back(0);
	for(int i = 1; i < 2 * N; i++) {
		q.push(input[i]);
		for(int j = 0; j < candidates.size(); j++) {
			unsigned long next = input[i] + candidates[j];
			if (next > MAX)
				break;
			q.push(next);
		}
		if (q.empty())
			break;
		lasttop = q.top();
		q.pop();
		while(true) {
			if (lasttop > last) {
				last = lasttop;
				candidates.push_back(last);
			}
			if (q.empty())
				break;

			nexttop = q.top();
			if (nexttop > lasttop + 1)
				break;
			lasttop = nexttop;
			q.pop();
		}
	}
	while(!q.empty()) {
		nexttop = q.top();
		q.pop();
		if (nexttop > last) {
			candidates.push_back(nexttop);
			last = nexttop;
		}
	}
	for(int i = 0; i < candidates.size(); i++) {
		printf("%u ", candidates[i]);
	}
	return true;
}

int main() {
	int cases, caseno = 0;
	unsigned int input[40] = {0};
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &N, &K);
		memset(input, 0, sizeof(unsigned int) * 20);
		for(int i = 0; i < N; i++) {
			scanf("%d", &input[2 * i]);
			input[2 * i + 1] = input[2 * i];
		}
		qsort(input, 2 * N, sizeof(unsigned int), cmp);
		fn(input);
	}
	return 0;
}





