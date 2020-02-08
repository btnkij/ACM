/**
* Number:p4013
* Title:数字梯形问题
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

const int MAXN=8000;
const int MAXM=1000000;

struct Edge
{
    int from,to,cap,dis,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to,int cap,int dis)
{
    edges[edge_id]=(Edge){from,to,cap,dis,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,0,-dis,head[to]};
    head[to]=edge_id++;
}

int src,dst;
int dis[MAXN],pre[MAXN];
bool vis[MAXN];
bool spfa()
{
    clr(dis,INF);
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
            if(!vis[e.to])
            {
                Q.push(e.to);
                vis[e.to]=true;
            }
        }
    }
    return dis[dst]<INF;
}
int mcmf()
{
    int mincost=0;
    while(spfa())
    {
        int u=dst,flow=INF;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            flow=min(flow,e.cap);
            u=e.from;
        }
        u=dst;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            e.cap-=flow, edges[pre[u]^1].cap+=flow;
            mincost+=flow*e.dis;
            u=e.from;
        }
    }
    return mincost;
}
void reset()
{
    for(int i = 0; i < edge_id; i += 2)
    {
        edges[i].cap += edges[i ^ 1].cap;
        edges[i ^ 1].cap = 0;
    }
}

int w[30][50];
int id[30][50];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    int m,n; readi(m,n);
    int tot=0;
    repne2(i,0,n,j,0,m+i)
    {
        readi(w[i][j]);
        id[i][j]=tot++;
    }
    int src2;
    src=tot*2+1, src2=tot*2+2, dst=tot*2+3;
    addedge(src, src2, m, 0);
    repne2(i,0,n,j,0,m+i)
    {
        addedge(id[i][j], id[i][j]+tot, 1, -w[i][j]);
        if(i==0)addedge(src2, id[i][j], 1, 0);
        if(i==n-1)addedge(id[i][j]+tot, dst, INF, 0);
        if(i<n-1)
        {
            addedge(id[i][j]+tot, id[i+1][j], 1, 0);
            addedge(id[i][j]+tot, id[i+1][j+1], 1, 0);
        }
    }
    printf("%d\n", -mcmf());
    reset();
    repne2(i,0,n,j,0,m+i)
    {
        addedge(id[i][j], id[i][j]+tot, INF, -w[i][j]);
    }
    printf("%d\n", -mcmf());
    reset();
    repne2(i,0,n-1,j,0,m+i)
    {
        addedge(id[i][j]+tot, id[i+1][j], INF, 0);
        addedge(id[i][j]+tot, id[i+1][j+1], INF, 0);
    }
    printf("%d", -mcmf());
    return 0;
}