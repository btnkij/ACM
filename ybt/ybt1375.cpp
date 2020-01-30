/**
* Number:ybt1375
* Title:骑马修栅栏(fence)
* Status:AC
* Tag:[欧拉回路]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <list>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int adj[600][600];
int f,path[600],dep;
void dfs(int u)
{
    rep(v,1,500)
    {
        if(adj[u][v])
        {
            adj[u][v]--, adj[v][u]--;
            dfs(v);
        }
    }
    path[dep++]=u;
}
int deg[600];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(f);
    repne(i,0,f)
    {
        int u,v; readi2(u,v);
        adj[u][v]++, adj[v][u]++;
        deg[u]++, deg[v]++;
    }
    int src=1;
    rep(i,1,500)
    {
        if(deg[i]&1)
        {
            src=i;
            break;
        }
    }
    dfs(src);
    for(int i=dep-1;i>=0;i--)printf("%d\n",path[i]);
    return 0;
}