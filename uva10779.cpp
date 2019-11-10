/**
* Number:uva10779
* Title:Collectors Problem
* Status:?
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

const int MAXN=100;
const int MAXM=4000;

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

int cnt[30];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    rep(kase,1,T)
    {
        int n,m; readi(n,m);
        src=1, dst=n+m+1;
        clr(head,-1); edgeid=0;
        int k; readi(k);
        clr(cnt,0);
        rep(i,1,k)
        {
            int t; readi(t);
            cnt[t]++;
        }
        rep(i,1,m)if(cnt[i])addflow(src,n+i,cnt[i]);
        rep(i,2,n)
        {
            readi(k);
            clr(cnt,0);
            while(k--)
            {
                int t; readi(t);
                cnt[t]++;
            }
            rep(j,1,m)
            {
                if(cnt[j]>1)addflow(i,n+j,cnt[j]-1);
                else if(!cnt[j])addflow(n+j,i,1);
            }
        }
        rep(i,1,m)addflow(n+i,dst,1);
        int maxflow=dinic();
        printf("Case #%d: %d\n",kase,maxflow);
    }
    return 0;
}