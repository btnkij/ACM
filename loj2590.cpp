/**
* Number:loj2590
* Title:「NOIP2009」最优贸易
* Status:AC
* Tag:[图, dp]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to;
}edges[500010*2];
int head[100010],nxt[500010*2],ne;
void add_edge(int from,int to)
{
    Edge& e=edges[ne];
    e.from=from, e.to=to;
    nxt[ne]=head[from];
    head[from]=ne++;
}

int v[100010], mincost[100010], reward[100010];
void dfs(int u, int cost, int pre)
{
    cost=min(v[u], cost);
    bool chg=false;
    if(cost<mincost[u])
    {
        mincost[u]=cost;
        chg=true;
    }
    int tmp=max(reward[pre], v[u]-cost);
    if(tmp>reward[u])
    {
        reward[u]=tmp;
        chg=true;
    }
    if(chg)
    {
        for(int i=head[u]; ~i; i=nxt[i])
        {
            dfs(edges[i].to, cost, u);
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    mset(head,-1);
    mset(mincost,INF);
    rep(i,1,n)readi(v[i]);
    while(m--)
    {
        int u,v,z; readi(u,v,z);
        add_edge(u,v);
        if(z==2)add_edge(v,u);
    }
    dfs(1, INF, 0);
    printf("%d",reward[n]);
    return 0;
}