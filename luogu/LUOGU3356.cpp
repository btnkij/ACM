/**
* Number:p3356
* Title:火星探险问题
* Status:AC
* Tag:[网络流, 最小费用最大流]
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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=4000;
const int MAXM=500000;
struct Edge
{
    int from,to,cap,r,dis,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to,int cap,int dis)
{
    edges[edge_id]=(Edge){from,to,cap,cap,dis,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,cap,0,-dis,head[to]};
    head[to]=edge_id++;
}

int src,dst;
int dis[MAXN],pre[MAXN];
bool vis[MAXN];
bool spfa()
{
    clr(dis,INF); dis[src]=0;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.r<=0 || dis[u]+e.dis>=dis[e.to])continue;
            dis[e.to]=dis[u]+e.dis;
            pre[e.to]=i;
            if(!vis[e.to])
            {
                vis[e.to]=true;
                Q.push(e.to);
            }
        }
    }
    return dis[dst]!=INF;
}
int mcmf()
{
    int mincost=0;
    while(spfa())
    {
        int u=dst,f=INF;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            f=min(f,e.r);
            u=e.from;
        }
        u=dst;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            e.r-=f;
            edges[pre[u]^1].r+=f;
            mincost+=e.dis*f;
            u=e.from;
        }
    }
    return mincost;
}

int maze[40][40],id[40][40],tot=0;
void print(int no,int u)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        if(i&1)continue;
        Edge& e=edges[i];
        if(e.cap==e.r)continue;
        e.r++;
        if(tot+1<=e.from && e.from<=(tot<<1) && 1<=e.to && e.to<=tot)
        {
            if(e.to==e.from-tot+1)printf("%d 1\n",no);
            else printf("%d 0\n",no);
        }
        print(no,e.to);
        return;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    int n,p,q; readi(n,q,p);
    rep2(i,1,p,j,1,q)
    {
        readi(maze[i][j]);
        id[i][j]=++tot;
    }
    src=tot*2+1, dst=tot*2+2;
    rep2(i,1,p,j,1,q)
    {
        if(maze[i][j]==1)continue;
        int x=id[i][j],y=x+tot;
        addedge(x,y,INF,0);
        if(maze[i][j]==2)addedge(x,y,1,-1);
        if(i<p && maze[i+1][j]!=1)addedge(y,id[i+1][j],INF,0);
        if(j<q && maze[i][j+1]!=1)addedge(y,id[i][j+1],INF,0);
    }
    addedge(src,id[1][1],n,0);
    addedge(id[p][q],dst,INF,0);
    mcmf();
    rep(i,1,n)print(i,src);
    return 0;
}