/**
* Number:loj10104
* Title:「一本通 3.6 练习 5」Blockade
* Status:AC
* Tag:[tarjan, 割点]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=1e5+10;
const int MAXM=5e5+10;
struct Edge
{
    int from,to,nxt;
}edges[MAXM*2];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]={from,to,head[from]};
    head[from]=edgeid++;
}

int n;
ll ans[MAXN],sz[MAXN];
int dfn[MAXN],low[MAXN],dfsid;
void tarjan(int u,int pre)
{
    dfn[u]=low[u]=++dfsid;
    ll sz1=sz[u]=1;
    int son=0;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        if(!dfn[v])
        {
            son++;
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            sz[u]+=sz[v];
            if(low[v]>=dfn[u])
            {
                ans[u]+=sz[v]*(n-sz[v]+1);
                sz1+=sz[v];
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
    if(pre==0 && son<2 || ans[u]==0)ans[u]=2*(n-1);
    else ans[u]+=(n-sz1)*(sz1+1);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m; readi(n,m);
    clr(head,-1), edgeid=0;
    while(m--)
    {
        int u,v; readi(u,v);
        addedge(u,v), addedge(v,u);
    }
    rep(i,1,n)if(!dfn[i])tarjan(i,0);
    rep(i,1,n)printf("%lld\n",ans[i]);
    return 0;
}