/*
ID: wentcui1
TASK: spin
LANG: C++
*/

#include <cstdio>
#include <cstring>
 
int main() {
    freopen("spin.in", "r", stdin), freopen("spin.out", "w", stdout);
    int v[5], nwidges[5], wd[5][5][2], open[360] = { 0 };
    for (int i = 0; i < 5; i++) {
        scanf("%d %d", v + i, nwidges + i);
        for (int j = 0; j < nwidges[i]; j++)
            scanf("%d %d", wd[i][j], wd[i][j] + 1);
    }
    for (int t = 0; t < 360; memset(open, 0, sizeof open), t++)
        for (int w = 0; w < 5; w++)
            for (int n = 0; n < nwidges[w]; n++)
                for (int p=t*v[w]+wd[w][n][0]; p<=t*v[w]+wd[w][n][0]+wd[w][n][1]; p++) {
                    if (++open[p % 360] == 5) {
                        printf("%d\n", t);
                        return 0;
                    }
                }
 
    puts("none");
}
