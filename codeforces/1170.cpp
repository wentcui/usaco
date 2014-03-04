#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>

#define PP pair<int, unsigned long>
#define MAX_V 10000000001
#define MOD 100000007

using namespace std;

int dp[10000] = {0};

struct cmp {
	bool operator() (const PP &p1, const PP &p2) {
		return p1.second > p2.second;
	}
};

int gen_pn(int *pn) {
	int curindex = 0, i;
	priority_queue<PP, vector<PP>, cmp> q;
	for(i = 2; i <= 100000; i++)
		q.push(make_pair(i, i * i));
	printf("%lu\n\n", q.top().second);

	/*
	while(!q.empty() && q.top().second < MAX_V) {
		unsigned long next;
		PP top = q.top();
		q.pop();
		pn[++curindex] = top.second;
		printf("%lu ", top.second);
		
		next = top.first * top.second;
		if (next < MAX_V)
			q.push(make_pair(top.first, next));
	}*/
	return curindex;
}

int bSearch(int *arr, int start, int end, int value) {
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
	int sum = 0;
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
	int pn[10000] = {0}, len;
	int cases, caseno = 0, s, e, ss, ee;
	len = gen_pn(pn);
	printf("len: %d\n", len);
	/*
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &s, &e);
		ss = bSearch(pn, 1, len - 1, s);
		ee = bSearch(pn, ss, len - 1, e);
		if (e == pn[ee])
			ee++;
		printf("Case %d: %d\n", ++caseno, get_tree_nr(ee - ss));
	}
	*/
	return 0;
}
