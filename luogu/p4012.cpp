/**
* Number:p4012
* Title:深海机器人问题
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
}edges[10000];
int head[300],edge_id;
void addedge(int from,int to,int cap,int dis)
{
    edges[edge_id]=(Edge){from,to,cap,dis,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,0,-dis,head[to]};
    head[to]=edge_id++;
}

int src,dst;
int dis[300],pre[300];
bool vis[300];
bool spfa()
{
    mset(dis,INF);
    dis[src]=0;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        // printf("pop dis[%d]=%d\n",u,dis[u]);
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.cap<=0 || dis[u]+e.dis>=dis[e.to])continue;
            dis[e.to]=dis[u]+e.dis;
            // printf("update dis[%d]=%d\n",e.to,dis[e.to]);
            pre[e.to]=i;
            if(!vis[e.to])
            {
                Q.push(e.to);
                vis[e.to]=true;
            }
        }
    }
    // puts("================================");
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

int id[20][20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    int a,b; readi(a,b);
    int p,q; readi(p,q);
    int tot=0;
    rep2(i,0,p,j,0,q)id[i][j]=tot++;
    src=tot, dst=tot+1;
    rep(i,0,p)
    {
        repne(j,0,q)
        {
            int c; readi(c);
            addedge(id[i][j],id[i][j+1],1,-c);
            addedge(id[i][j],id[i][j+1],INF,0);
        }
    }
    rep(j,0,q)
    {
        repne(i,0,p)
        {
            int c; readi(c);
            addedge(id[i][j],id[i+1][j],1,-c);
            addedge(id[i][j],id[i+1][j],INF,0);
        }
    }
    repne(i,0,a)
    {
        int k,x,y; readi(k,x,y);
        addedge(src,id[x][y],k,0);
    }
    repne(i,0,b)
    {
        int r,x,y; readi(r,x,y);
        addedge(id[x][y],dst,r,0);
    }
    printf("%d",-mcmf());
    return 0;
}