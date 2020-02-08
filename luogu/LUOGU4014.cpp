/**
* Number:p4014
* Title:分配问题
* Status:AC
* Tag:[最小费用最大流]
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

const int MAXN=110;
const int MAXM=MAXN*MAXN*2;
struct Edge
{
    int from,to,cap,cost;
}edges[MAXM];
int head[MAXN],nxt[MAXM],tot;
void add1(int from,int to,int cap,int cost)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.cap=cap, e.cost=cost;
    nxt[tot]=head[from];
    head[from]=tot++;
}
void add2(int from,int to,int cap,int cost)
{
    add1(from,to,cap,cost);
    add1(to,from,0,-cost);
}
int src,dst;
int dis[MAXN],pre[MAXN];
bool vis[MAXN];
bool spfa()
{
    queue<int> Q;
    Q.push(src);
    mset(dis,INF); dis[src]=0;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=nxt[i])
        {
            Edge& e=edges[i];
            if(!e.cap || dis[u]+e.cost>=dis[e.to])continue;
            dis[e.to]=dis[u]+e.cost;
            pre[e.to]=i;
            if(!vis[e.to])
            {
                Q.push(e.to);
                vis[e.to]=true;
            }
        }
    }
    return dis[dst]!=INF;
}
int maxflow,mincost;
void mcmf()
{
    maxflow=mincost=0;
    while(spfa())
    {
        int f=INF, u=dst;
        while(u!=src)
        {
            f=min(f,edges[pre[u]].cap);
            u=edges[pre[u]].from;
        }
        maxflow+=f;
        u=dst;
        while(u!=src)
        {
            edges[pre[u]].cap-=f;
            edges[pre[u]^1].cap+=f;
            mincost+=f*edges[pre[u]].cost;
            u=edges[pre[u]].from;
        }
    }
}

int adj[MAXN][MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    int n; readi(n);
    src=0,dst=n*2+1;
    rep(i,1,n)
    {
        add2(src,i,1,0);
        add2(n+i,dst,1,0);
    }
    int tmp=tot;  
    rep2(i,1,n,j,1,n)
    {
        readi(adj[i][j]);
        add2(i,n+j,1,adj[i][j]);
    }
    mcmf();
    printf("%d\n",mincost);
    for(int i=0;i<tmp;i+=2)
    {
        edges[i].cap=1;
        edges[i|1].cap=0;
    }
    rep2(i,1,n,j,1,n)
    {
        edges[tmp].cap=1, edges[tmp].cost=-adj[i][j];
        tmp++;
        edges[tmp].cap=0, edges[tmp].cost=adj[i][j];
        tmp++;
    }
    mcmf();
    printf("%d",-mincost);
    return 0;
}