/**
* Number:p4015
* Title:运输问题
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
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to,cap,dis,nxt;
}edges[40010];
int head[410],edge_id;
void addedge(int from,int to,int cap,int dis)
{
    edges[edge_id]=(Edge){from,to,cap,dis,head[from]};
    head[from]=edge_id++;
}

int nx,ny,src,dst;
int dis[410],pre[410];
bool vis[410];
bool spfa()
{
    mset(dis,INF);
    dis[src]=0;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.cap<=0 || dis[u]+e.dis>=dis[e.to])continue;
            dis[e.to]=dis[u]+e.dis;
            pre[e.to]=i;
            if(vis[e.to])continue;
            vis[e.to]=true;
            Q.push(e.to);
        }
    }
    return dis[dst]<INF;
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
            f=min(f,e.cap);
            u=e.from;
        }
        u=dst;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            e.cap-=f;
            edges[pre[u]^1].cap+=f;
            mincost+=f*e.dis;
            u=e.from;
        }
    }
    return mincost;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(nx,ny);
    mset(head,-1);
    src=nx+ny+1, dst=src+1;
    rep(i,1,nx)
    {
        int a; readi(a);
        addedge(src,i,a,0); addedge(i,src,0,0);
    }
    repne(i,nx+1,src)
    {
        int b; readi(b);
        addedge(i,dst,b,0); addedge(dst,i,0,0);
    }
    rep(i,1,nx)
    {
        repne(j,nx+1,src)
        {
            int c; readi(c);
            addedge(i,j,INF,c); addedge(j,i,0,-c);
        }
    }
    printf("%d\n",mcmf());
    for(int i=0;i<edge_id;i+=2)
    {
        Edge &e1=edges[i], &e2=edges[i^1];
        e1.cap+=e2.cap, e2.cap=0;
        e1.dis=-e1.dis, e2.dis=-e2.dis;
    }
    printf("%d",-mcmf());
    return 0;
}