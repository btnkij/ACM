/**
* Number:uva1659
* Title:Help Little Laura
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

const double eps=1e-6;
const int MAXN=210;
const int MAXM=80000;

struct Edge
{
    int from,to,flow;
    double dis;
    int nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int flow,double dis)
{
    edges[edgeid]=(Edge){from,to,flow,dis,head[from]};
    head[from]=edgeid++;
}

int src,dst,pre[MAXN];
double dis[MAXN];
bool vis[MAXN];
void addflow(int from,int to,int flow,double dis)
{
    addedge(from,to,flow,dis);
    addedge(to,from,0,-dis);
}
bool spfa(int n)
{
    fill_n(dis,n+1,1e35); dis[src]=0;
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
    return dis[dst]<1e30;
}
double mcmf(int n)
{
    double mincost=0;
    while(spfa(n))
    {
        for(int u=dst;u!=src;u=edges[pre[u]].from)
        {
            edges[pre[u]].flow--;
            edges[pre[u]^1].flow++;
            mincost+=edges[pre[u]].dis;
        }
    }
    return mincost;
}

vector<pair<int,int> > link;
int x[MAXN],y[MAXN],deg[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,kase=1;
    while(readi(n)!=EOF && n)
    {
        int w1,w2; readi(w1,w2);
        link.clear();
        rep(i,1,n)
        {
            readi(x[i],y[i]);
            int v;
            while(readi(v)!=EOF && v)link.emplace_back(i,v);
        }
        clr(head,-1); edgeid=0;
        clr(deg,0);
        double ans=0;
        for(auto it:link)
        {
            int u=it.first, v=it.second;
            double dis=sqrt(pow(x[u]-x[v],2)+pow(y[u]-y[v],2))*w1-w2;
            if(dis<-eps)addflow(u,v,1,-dis);
            else if(dis>eps)
            {
                ans+=-dis;
                addflow(v,u,1,dis);
                deg[u]++, deg[v]--;
            }
        }
        src=n+1, dst=n+2;
        rep(i,1,n)
        {
            if(deg[i]>0)addflow(i,dst,deg[i],0);
            else if(deg[i]<0)addflow(src,i,-deg[i],0);
        }
        ans=-(mcmf(dst)+ans)+eps;
        printf("Case %d: %.2lf\n",kase++,ans);
    }
    return 0;
}

/**
* Number:uva1659
* Title:Help Little Laura
* Status:AC
* Tag:[网络流, 最小费用循环流, spfa, 负环]
**/

/*
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
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

const int MAXN=210;
const int MAXM=80000;

struct Edge
{
    int from,to,flow;
    double dis;
    int nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int flow)
{
    edges[edgeid]=(Edge){from,to,flow,0,head[from]};
    head[from]=edgeid++;
}
void addflow(int from,int to,int flow)
{
    addedge(from,to,flow);
    addedge(to,from,0);
}

int src,dst;
int path[MAXN];
double dis[MAXN];
bool vis[MAXN];

int spfa(int u)
{
    int ans=-1;
    vis[u]=true;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(e.flow==0 || dis[e.to]<=dis[u]+e.dis)continue;
        dis[e.to]=dis[u]+e.dis;
        path[e.to]=i;
        if(vis[e.to] && (ans=e.to))break;
        if((ans=spfa(e.to))!=-1)break;
    }
    vis[u]=false;
    return ans;
}
double mcmf(int n)
{
    double mincost=0;
    while(true)
    {
        fill_n(dis,n+1,0);
        int root=-1;
        rep(i,1,n)if((root=spfa(i))!=-1)break;
        if(root==-1)break;
        int u=root;
        do{
            edges[path[u]].flow--;
            edges[path[u]^1].flow++;
            mincost+=edges[path[u]].dis;
            u=edges[path[u]].from;
        }while(edges[path[u]].to!=root);
    }
    return mincost;
}

int x[MAXN],y[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,kase=1;
    while(readi(n)!=EOF && n)
    {
        clr(head,-1); edgeid=0;
        int w1,w2; readi(w1,w2);
        rep(i,1,n)
        {
            readi(x[i],y[i]);
            int v;
            while(readi(v)!=EOF && v)addflow(i,v,1);
        }
        for(int i=0;i<edgeid;i+=2)
        {
            int u=edges[i].from, v=edges[i].to;
            double dis=sqrt(pow(x[u]-x[v],2)+pow(y[u]-y[v],2))*w1-w2;
            edges[i].dis=-dis, edges[i^1].dis=dis;
        }
        double ans=-mcmf(n);
        printf("Case %d: %.2lf\n",kase++,ans+1e-6);
    }
    return 0;
}
*/