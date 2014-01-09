/*
ID: wentcui1
LANG: C++
TASK: rockers
*/

#include <fstream>

using namespace std;

const int MAX = 25;

int f[MAX][MAX][MAX];
int cost[MAX];

int N,T,M;

inline int max(int a, int b){
    return a>b? a: b;
}

int main(){
    int i,j,k;

    ifstream fin("rockers.in");
    ofstream fout("rockers.out");

    fin>>N>>T>>M;

    for(i=1; i<=N; ++i)
        fin>>cost[i];

    for(i=1; i<=N; ++i)
        for(j=1; j<=M; ++j)
            for(k=1; k<=T; ++k)
                if(k<cost[i])
                    f[i][j][k] = max(f[i-1][j][k], f[i-1][j-1][T]); 
                else
                    f[i][j][k] = max(f[i-1][j][k-cost[i]], f[i-1][j-1][T])+1;

    fout<<f[N][M][T]<<endl;
            

    return 0;
}
