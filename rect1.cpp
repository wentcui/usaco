/*
ID: wentcui1
TASK: rect1
LANG: C++
*/
#include <cstdio>
#include <algorithm>
using namespace std;
 
struct Rectangle { int ax, ay, bx, by, c; } rec[100001];
int main() {
    freopen("rect1.in", "r", stdin), freopen("rect1.out", "w", stdout);
    int W, H, N, top=0, cut[100000]= {0}, count[2501]={0}, ax, ay, bx, by, c;
    scanf("%d %d %d", &W, &H, &N);
 
    rec[top++] = Rectangle {0,0,W,H,1};
    for(int i=0; i<N; ++i){
        scanf("%d %d %d %d %d", &ax, &ay, &bx, &by, &c);
        rec[top++]= Rectangle{ax, ay, bx, by, c};
        for(int j=0, J=top-1; j<J; ++j)
            if(!cut[j]){
                int max_ax = max(ax, rec[j].ax), max_ay = max(ay, rec[j].ay);
                int min_bx = min(bx, rec[j].bx), min_by = min(by, rec[j].by);
                if(max_ax >= min_bx || max_ay >= min_by) continue; else cut[j]++;
                rec[top++] = Rectangle { rec[j].ax, rec[j].ay, min_bx   , max_ay   , rec[j].c};
                rec[top++] = Rectangle { min_bx   , rec[j].ay, rec[j].bx, min_by   , rec[j].c};
                rec[top++] = Rectangle { rec[j].ax, max_ay   , max_ax   , rec[j].by, rec[j].c};
                rec[top++] = Rectangle { max_ax   , min_by   , rec[j].bx, rec[j].by, rec[j].c};
            }
    }
    for(int i=0; i<top; ++i)
        if(!cut[i])
            count[rec[i].c] += (rec[i].bx- rec[i].ax)*(rec[i].by- rec[i].ay);
 
    for(int i=1; i<=2500; ++i)
        if(count[i]>0)
            printf("%d %d\n", i, count[i]);
}
