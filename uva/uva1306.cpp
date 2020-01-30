/**
* Number:uva1306
* Title:The K-League
* Status:AC
* Tag:[网络流, 最大流]
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

const int MAXN=2000;
const int MAXM=8000;

struct Edge
{
    int from,to,flow,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int flow)
{
    edges[edgeid]=(Edge){from,to,flow,head[from]};
    head[from]=edgeid++;
}

int src,dst,dep[MAXN],cur[MAXN];
void addflow(int from,int to,int flow)
{
    addedge(from,to,flow);
    addedge(to,from,0);
}
bool getdep()
{
    clr(dep,0); dep[src]=1;
    queue<int> Q; Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(dep[e.to] || e.flow==0)continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst];
}
int augment(int u,int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(e.flow==0 || dep[u]+1!=dep[e.to])continue;
        int f=augment(e.to,min(flow,e.flow));
        if(f)
        {
            e.flow-=f, edges[i^1].flow+=f;
            return f;
        }
    }
    return 0;
}
int dinic()
{
    int maxflow=0,f;
    while(getdep())
    {
        memcpy(cur,head,sizeof(head));
        while(f=augment(src,INF))maxflow+=f;
    }
    return maxflow;
}

int w[30],d[30],a[30][30],sumw[30],id[30][30];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        rep(i,1,n)readi(w[i],d[i]);
        int sum=0;
        clr(sumw,0);
        rep2(i,1,n,j,1,n)
        {
            readi(a[i][j]);
            sum+=a[i][j];
            sumw[i]+=a[i][j];
        }
        sum>>=1;
        int now=n;
        rep2(i,1,n,j,i+1,n)id[i][j]=++now;
        src=now+1, dst=now+2;
        bool first=true;
        rep(i,1,n)
        {
            int tot=sumw[i]+w[i];
            if(any_of(w+1,w+n+1,[tot](int x){return x>tot;}))continue;
            clr(head,-1); edgeid=0;
            rep2(i,1,n,j,i+1,n)
            {
                addflow(id[i][j],i,INF);
                addflow(id[i][j],j,INF);
                addflow(src,id[i][j],a[i][j]);
            }
            rep(i,1,n)addflow(i,dst,tot-w[i]);
            if(dinic()==sum)
            {
                if(!first)putchar(' ');
                first=false;
                printf("%d",i);
            }
        }
        puts("");
    }
    return 0;
}