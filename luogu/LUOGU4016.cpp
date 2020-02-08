/**
* Number:p4016
* Title:负载平衡问题
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
struct Edge
{
    int from,to,cap,dis;
}edges[MAXN<<3];
int head[MAXN],nxt[MAXN<<3];
int n,m;
void add_edge(int from,int to,int cap,int dis)
{
    Edge& e=edges[m];
    e.from=from, e.to=to, e.cap=cap, e.dis=dis;
    nxt[m]=head[from], head[from]=m;
    m++;
}
void add2(int from,int to,int cap,int dis)
{
    add_edge(from,to,cap,dis);
    add_edge(to,from,0,-dis);
}

bool vis[MAXN];
int dis[MAXN],pre[MAXN];
int src,dst;
bool spfa()
{
    memset(vis,false,sizeof(bool)*(n+2));
    memset(dis,INF,sizeof(int)*(n+2));
    queue<int> Q;
    Q.push(src);
    dis[src]=0;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u]; ~i; i=nxt[i])
        {
            Edge& e=edges[i];
            if(e.cap && e.dis+dis[u]<dis[e.to])
            {
                dis[e.to]=e.dis+dis[u];
                pre[e.to]=i;
                if(!vis[e.to])
                {
                    vis[e.to]=true;
                    Q.push(e.to);
                }
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
        int f=INF,u=dst;
        while(u!=src)
        {
            f=min(f,edges[pre[u]].cap);
            u=edges[pre[u]].from;
        }
        u=dst;
        while(u!=src)
        {
            edges[pre[u]].cap-=f;
            edges[pre[u]^1].cap+=f;
            mincost+=f*edges[pre[u]].dis;
            u=edges[pre[u]].from;
        }
    }
    return mincost;
}

int num[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n);
    memset(head,-1,sizeof(int)*(n+2));
    src=0, dst=n+1;
    int ave=0;
    rep(i,1,n)
    {
        readi(num[i]);
        ave+=num[i];
        add2(i,(i-2+n)%n+1,INF,1);
        add2(i,i%n+1,INF,1);
    }
    ave/=n;
    rep(i,1,n)
    {
        add2(src,i,num[i],0);
        add2(i,dst,ave,0);
    }
    int ans=mcmf();
    printf("%d",ans);
    return 0;
}