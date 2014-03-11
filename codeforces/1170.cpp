#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>

#define PP pair<int, unsigned long>
#define MAX_V 10000000001
#define MOD 100000007

using namespace std;

int dp[102232] = {0};

struct cmp {
	bool operator() (const PP &p1, const PP &p2) {
		return p1.second > p2.second;
	}
};

int gen_pn(unsigned long *pn) {
	int curindex = 0;
	unsigned long v, i;
	priority_queue<PP, vector<PP>, cmp> q;
	for(i = 2; i <= 100000; i++){
		v = i * i;
		q.push(make_pair(i, v));
	}

	while(!q.empty() && q.top().second < MAX_V) {
		unsigned long next;
		PP top = q.top();
		q.pop();
		if (top.second != pn[curindex]) {
			pn[++curindex] = top.second;
//			printf("i: %d, first: %d, %lu\n", curindex, top.first, top.second);
		}
		next = top.first * top.second;
		if (next < MAX_V)
			q.push(make_pair(top.first, next));
	}
	return curindex;
}

int bSearch(unsigned long *arr, int start, int end, unsigned long value) {
	int mid, l = start, r = end;
	if (value <= 0)
		return 1;
	while(l < r) {
		mid = l + (r - l) / 2;
		if (arr[mid] < value)
			l = mid + 1;
		else
			r = mid;
	}
	return l;
}


int get_tree_nr(int nr) {
	unsigned long sum = 0;
	if (nr < 0)
		return 0;
	if (!nr || nr == 1)
		return 1;
	if (dp[nr] > 0)
		return dp[nr];

	for(int i = 1; i <= nr; i++)
		sum += ((get_tree_nr(i - 1) % MOD) * (get_tree_nr(nr - i) % MOD));

	dp[nr] = sum % MOD;
	return dp[nr];
}


int main() {
	unsigned long pn[102232] = {0}, s, e;
	int cases, caseno = 0, ss, ee, len;
	len = gen_pn(pn);
	scanf("%d", &cases);
	while(cases--) {
		scanf("%lu %lu", &s, &e);
		ss = bSearch(pn, 1, len, s);
		ee = bSearch(pn, ss, len, e);
		
		if (e == pn[ee])
			ee++;
		//printf("%lu, %d, %lu\n", e, ee, pn[ee]);
		//printf("ss: %d, ee: %d\n", ss, ee);
		if (ee == ss)
			printf("Case %d: 0\n", ++caseno);
		else
			printf("Case %d: %d\n", ++caseno, get_tree_nr(ee - ss));
	}

	return 0;
}
