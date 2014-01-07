/*
ID: wentcui1
PROG: camelot
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <iomanip>
#include <queue>
#include <map>
#include <stack>
using namespace std;
 
ofstream fout("camelot.out");
ifstream fin("camelot.in");
 
int king[2];
vector < pair<int, int> > knight;
int R, C;
int color[26][30];
int d[26][30][26][30];
 
int step[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};
 
void bfs(int x, int y)
{
    for (int i = 0; i < C; i++)
    for (int j = 0; j < R; j++)
    {
        color[i][j] = 0;
        d[x][y][i][j] = 9999999;
    }
    color[x][y] = 1;
    d[x][y][x][y] = 0;
    queue < pair <int, int> > Q;
    Q.push(make_pair(x, y));
    while(!Q.empty())
    {
        int ux = Q.front().first;
        int uy = Q.front().second;
        Q.pop();
        for (int i = 0; i < 8; i++)
        {
            int vx = ux + step[i][0];
            int vy = uy + step[i][1];
            if ( vx < 0 || vx >= C || vy < 0 || vy >= R) continue;
            if (color[vx][vy] == 0)
            {
                color[vx][vy] = 1;
                d[x][y][vx][vy] = d[x][y][ux][uy] + 1;
                Q.push(make_pair(vx, vy));
            }
        }
    }
}
 
int calc(int x, int y)
{
    int sum = 0;
    for (int i = 0; i < knight.size(); i++)
        sum += d[knight[i].first][knight[i].second][x][y];
    // king alone
    int res = sum + max(abs(king[0]-x), abs(king[1]-y));
    // pick up
    for (int tx = max(0, king[0]-2); tx <= min(C-1, king[0]+2); tx++)
    for (int ty = max(0, king[1]-2); ty <= min(R-1, king[1]+2); ty++)
    for (int i = 0; i < knight.size(); i++)
        res = min(res, sum - d[knight[i].first][knight[i].second][x][y] + d[knight[i].first][knight[i].second][tx][ty] + d[tx][ty][x][y] + max(abs(king[0]-tx), abs(king[1]-ty)));
    return res;
}
 
int main()
{
    fin >> R >> C;
    char tempc;
    int tempi;
    fin >> tempc >> tempi;
    king[0] = tempc-'A';
    king[1] = tempi-1;
    while(fin >> tempc)
    {
        fin >> tempi;
        knight.push_back(make_pair(tempc-'A', tempi-1));
    }
    // calc the shortest path
    for (int i = 0; i < C; i++)
    for (int j = 0; j < R; j++)
        bfs(i, j);
    // calc the min move
    int res = 1e9;
    for (int i = 0; i < C; i++)
    for (int j = 0; j < R; j++)
        res = min(res, calc(i, j));
    fout << res << endl;
    return 0;
}
