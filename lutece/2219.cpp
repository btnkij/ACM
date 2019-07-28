/**
* Number:2219
* Title:zh吃饭
* Status:AC
* Tag:[缩点, dp]
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=3010;
struct Edge
{
    int from,to,nxt;
};
struct Graph
{
    Edge edges[MAXN];
    int head[MAXN],edge_id;
    void addedge(int from,int to)
    {
        edges[edge_id]=(Edge){from,to,head[from]};
        head[from]=edge_id++;
    }
}G,N;

int like[MAXN],dst[MAXN],dp[MAXN];

int dfn[MAXN],dfs_id,low[MAXN];
int grp[MAXN],grp_id;
stack<int> trace;
void tarjan(int u)
{
    dfn[u]=low[u]=++dfs_id;
    trace.push(u);
    for(int i=G.head[u];~i;i=G.edges[i].nxt)
    {
        int v=G.edges[i].to;
        if(!dfn[v])tarjan(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
        grp_id++;
        int tmp;
        do{
            tmp=trace.top(); trace.pop();
            grp[tmp]=grp_id;
            dp[grp_id]+=like[tmp];
        }while(tmp!=u);
    }
}

void shrink()
{
    for(int i=0;i<G.edge_id;i++)
    {
        Edge& e=G.edges[i];
        if(grp[e.from]==grp[e.to])continue;
        N.addedge(grp[e.to],grp[e.from]);
    }
}

bool vis[MAXN];
void dfs(int u)
{
    if(vis[u])return;
    vis[u]=true;
    int tmp=0;
    for(int i=N.head[u];~i;i=N.edges[i].nxt)
    {
        int v=N.edges[i].to;
        dfs(v);
        tmp=max(tmp,dp[v]);
    }
    dp[u]+=tmp;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)G.head[i]=N.head[i]=-1;
    repne(i,0,m)
    {
        int u,v; readi(u,v);
        G.addedge(u,v);
    }
    rep(i,1,n)readi(like[i]);
    int s,p; readi(s,p);
    repne(i,0,p)readi(dst[i]);
    tarjan(s);
    shrink();
    dfs(grp[s]);
    int ans=-INF;
    repne(i,0,p)
    {
        int u=grp[dst[i]];
        dfs(u);
        ans=max(ans,dp[u]);
    }
    printf("%d",ans);
    return 0;
}