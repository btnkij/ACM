/**
* Number:loj10096
* Title:「一本通 3.5 练习 4」抢掠计划
* Status:AC
* Tag:[tarjan, 缩点, spfa, 最长路]
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

const int MAXN=500010;
const int MAXM=1000010;
struct Edge
{
    int from,to,nxt;
};
struct Graph
{
    Edge edges[MAXM];
    int head[MAXN],edgeid;
    int w[MAXN];
    void init()
    {
        clr(head,-1);
        edgeid=0;
    }
    void addedge(int from,int to)
    {
        edges[edgeid]=(Edge){from,to,head[from]};
        head[from]=edgeid++;
    }
}G,DAG;

int dfsid,dfn[MAXN],low[MAXN];
int grpid,grp[MAXN];
stack<int> trace;
void scc(int u)
{
    dfn[u]=low[u]=++dfsid;
    trace.push(u);
    for(int i=G.head[u];~i;i=G.edges[i].nxt)
    {
        int v=G.edges[i].to;
        if(!dfn[v])scc(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(low[u]==dfn[u])
    {
        ++grpid;
        int t;
        do
        {
            t=trace.top(); trace.pop();
            grp[t]=grpid;
            DAG.w[grpid]+=G.w[t];
        }while(t!=u);
    }
}

int dis[MAXN];
bool vis[MAXN];
int spfa(int src,int dst)
{
    clr(dis,-1);
    dis[src]=DAG.w[src];
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=DAG.head[u];~i;i=DAG.edges[i].nxt)
        {
            int v=DAG.edges[i].to;
            if(dis[u]+DAG.w[v]>dis[v])
            {
                dis[v]=dis[u]+DAG.w[v];
                if(!vis[v])Q.push(v),vis[v]=true;
            }
        }
    }
    return dis[dst];
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    G.init(), DAG.init();
    repne(i,0,m)
    {
        int u,v; readi(u,v);
        G.addedge(u,v);
    }
    rep(i,1,n)readi(G.w[i]);
    int src,dst;
    int p; readi(src,p);
    dst=n+1;
    repne(i,0,p)
    {
        int t; readi(t);
        G.addedge(t,dst);
    }
    scc(src);
    repne(i,0,G.edgeid)
    {
        Edge& e=G.edges[i];
        int u=grp[e.from],v=grp[e.to];
        if(u==v)continue;
        DAG.addedge(u,v);
    }
    src=grp[src],dst=grp[dst];
    int ans=spfa(src,dst);
    printf("%d",ans);
    return 0;
}