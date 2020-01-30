/**
* Number:uva1658
* Title:Admiral
* Status:AC
* Tag:[网络流, 最小费用最大流]
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

const int MAXN=10000;
const int MAXM=200000;

struct Edge
{
    int from,to;
    ll flow,dis;
    int nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,ll flow,ll dis)
{
    edges[edgeid]=(Edge){from,to,flow,dis,head[from]};
    head[from]=edgeid++;
}

int src,dst;
int pre[MAXN];
ll dis[MAXN];
bool vis[MAXN];
void addflow(int from,int to,ll flow,ll dis)
{
    addedge(from,to,flow,dis);
    addedge(to,from,0,-dis);
}
bool spfa()
{
    clr(dis,INF); dis[src]=0;
    queue<int> Q; Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.flow==0 || dis[u]+e.dis>=dis[e.to])continue;
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
ll mcmf()
{
    ll mincost=0;
    while(spfa())
    {
        ll f=INF;
        for(int u=dst;u!=src;u=edges[pre[u]].from)
            f=min(f,edges[pre[u]].flow);
        for(int u=dst;u!=src;u=edges[pre[u]].from)
        {
            edges[pre[u]].flow-=f;
            edges[pre[u]^1].flow+=f;
            mincost+=f*edges[pre[u]].dis;
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
    int n,m;
    while(readi(n,m)!=EOF)
    {
        clr(head,-1); edgeid=0;
        src=1, dst=n*2;
        addflow(src,n+1,2,0);
        addflow(n,dst,2,0);
        repne(i,2,n)addflow(i,n+i,1,0);
        rep(i,1,m)
        {
            int a,b,c; readi(a,b,c);
            addflow(n+a,b,1,c);
        }
        ll mincost=mcmf();
        printf("%lld\n",mincost);
    }
    return 0;
}