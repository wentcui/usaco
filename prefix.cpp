/*
ID: wentcui1
PROG: prefix
LANG: C++
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
 
using namespace std;
 
int main() {
    int best = -1, n = -1, v[200001] = { 0 }, sz[202];
	int longest = 0;
    char pre[202][11], s[200002], t[80];
    freopen("prefix.in", "r", stdin), freopen("prefix.out", "w", stdout);
 
    do {
        scanf("%s", pre[++n]);
        sz[n] = strlen(pre[n]);
		if (sz[n] > longest)
			longest = sz[n];
    } while (pre[n][0] != '.');
    while (scanf("%s", t) != -1)
        strncat(s, t, sizeof t);
     
    stack<int> stk; stk.push(0);
     
    while (stk.size()) {
        int from = stk.top(); stk.pop();
        best = max(best, from);
        for (int i = 0; i < n; i++) 
            if (!strncmp(s + from, pre[i], sz[i]) && !(v[from + sz[i]]++))
                stk.push(from + sz[i]);
    }
    printf("%d\n", best);
    return 0;
}
