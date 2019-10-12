/**
* Number:loj10095
* Title:「一本通 3.5 练习 3」间谍网络
* Status:AC
* Tag:[tarjan]
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

const int MAXN=3010;
const int MAXM=8010;
struct Edge
{
    int from,to,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int cost[MAXN],sccCost[MAXN];
int dfsid,dfn[MAXN],low[MAXN];
int grpid,grp[MAXN];
stack<int> trace;
void scc(int u)
{
    dfn[u]=low[u]=++dfsid;
    trace.push(u);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!dfn[v])scc(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(low[u]==dfn[u])
    {
        ++grpid;
        int t,tmp=INF;
        do
        {
            t=trace.top(); trace.pop();
            grp[t]=grpid;
            tmp=min(tmp,cost[t]);
        }while(t!=u);
        sccCost[grpid]=tmp;
    }
}

int indeg[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,p; readi(n,p);
    clr(cost,INF);
    while(p--)
    {
        int u,c; readi(u,c);
        cost[u]=c;
    }
    int r; readi(r);
    clr(head,-1);
    repne(i,0,r)
    {
        int u,v; readi(u,v);
        addedge(u,v);
    }
    rep(i,1,n)if(!dfn[i] && cost[i]!=INF)scc(i);
    rep(i,1,n)if(!dfn[i])
    {
        printf("NO\n%d",i);
        return 0;
    }
    repne(i,0,r)
    {
        int u=edges[i].from,v=edges[i].to;
        if(grp[u]==grp[v])continue;
        indeg[grp[v]]++;
    }
    int ans=0;
    rep(i,1,grpid)if(indeg[i]==0)ans+=sccCost[i];
    printf("YES\n%d",ans);
    return 0;
}