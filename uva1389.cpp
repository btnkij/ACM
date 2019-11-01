/**
* Number:uva1389
* Title:Hard Life
* Status:AC
* Tag:[网络流, 最大权闭合子图, 最小割]
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

#define INF 1e100
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
const int MAXN=2010;
const int MAXM=200010;

struct Edge
{
    int from,to;
    double flow;
    int nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,double flow)
{
    edges[edgeid]=(Edge){from,to,flow,head[from]};
    head[from]=edgeid++;
}
void addflow(int from,int to,double flow)
{
    addedge(from,to,flow);
    addedge(to,from,0);
}

int src,dst;
int dep[MAXN];
bool getdep()
{
    clr(dep,0);
    dep[src]=1;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.flow<eps || dep[e.to])continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]>0;
}
int cur[MAXN];
double augment(int u,double flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i && flow>eps;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(e.flow<eps || dep[u]+1!=dep[e.to])continue;
        double f=augment(e.to,min(flow,e.flow));
        if(f>eps)
        {
            e.flow-=f, edges[i^1].flow+=f;
            return f;
        }
    }
    return 0;
}
double dinic()
{
    double maxflow=0,f;
    while(getdep())
    {
        memcpy(cur,head,sizeof(head));
        while((f=augment(src,INF))>eps)maxflow+=f;
    }
    return maxflow;
}

vector<pair<int,int> > rel;
bool check(int n,int m,double mid)
{
    clr(head,-1); edgeid=0;
    rep(i,1,m)addflow(src,i,1);
    rep(i,1,n)addflow(m+i,dst,mid);
    for(int i=0;i<rel.size();i++)
    {
        addflow(i+1,rel[i].first+m,INF);
        addflow(i+1,rel[i].second+m,INF);
    }
    double maxw=m-dinic();
    return maxw<=0;
}

bool vis[MAXN];
void dfs(int u)
{
    vis[u]=true;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(!vis[e.to] && e.flow>0)dfs(e.to);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    bool first=true;
    while(readi(n,m)!=EOF)
    {
        if(!first)printf("\n");
        first=false;
        if(m==0)
        {
            printf("1\n1\n");
            continue;
        }
        rel.clear();
        repne(i,0,m)
        {
            int u,v; readi(u,v);
            rel.emplace_back(u,v);
        }
        src=m+n+1,dst=src+1;
        double lt=0,rt=m;
        while(rt-lt>eps)
        {
            double mid=(lt+rt)/2;
            if(check(n,m,mid))rt=mid;
            else lt=mid;
        }
        check(n,m,lt);
        vector<int> choice;
        clr(vis,false);
        dfs(src);
        printf("%d\n",count(vis+m+1,vis+m+n+1,true));
        rep(i,1,n)if(vis[m+i])printf("%d\n",i);
    }
    return 0;
}