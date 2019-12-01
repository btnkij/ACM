/**
* Number:loj10092
* Title:「一本通 3.5 例 2」最大半连通子图
* Status:AC
* Tag:[tarjan, dp]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <set>
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

const int MAXN=1e5+10;
const int MAXM=1e6+10;
struct Edge
{
    int from,to,nxt;
};
struct
{
    Edge edges[MAXM];
    int head[MAXN],edgeid;
    void addedge(int from,int to)
    {
        edges[edgeid]=(Edge){from,to,head[from]};
        head[from]=edgeid++;
    }
}G,DAG;

int dfsid,dfn[MAXN],low[MAXN];
int grpid,grp[MAXN],rk[MAXN];
stack<int> trace;
void tarjan(int u)
{
    dfn[u]=low[u]=++dfsid;
    trace.push(u);
    for(int i=G.head[u];~i;i=G.edges[i].nxt)
    {
        int v=G.edges[i].to;
        if(!dfn[v])tarjan(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
        int t;
        ++grpid;
        do
        {
            t=trace.top(); trace.pop();
            grp[t]=grpid, rk[grpid]++;
        }while(t!=u);
    }
}

int x;
int dp[MAXN],cnt[MAXN];
void dfs(int u)
{
    if(dp[u]!=-1)return;
    int ans1=0,ans2=1;
    for(int i=DAG.head[u];~i;i=DAG.edges[i].nxt)
    {
        int v=DAG.edges[i].to;
        dfs(v);
        if(ans1<dp[v])ans1=dp[v],ans2=cnt[v];
        else if(ans1==dp[v])ans2=(ans2+cnt[v])%x;
    }
    dp[u]=ans1+rk[u],cnt[u]=ans2;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(G.head,-1);
    int n,m; readi(n,m,x);
    repne(i,0,m)
    {
        int u,v; readi(u,v);
        G.addedge(u,v);
    }
    rep(i,1,n)if(!dfn[i])tarjan(i);
    clr(DAG.head,-1);
    set<pair<int,int> > S;
    repne(i,0,G.edgeid)
    {
        Edge& e=G.edges[i];
        int u=grp[e.from],v=grp[e.to];
        if(u==v || S.count(make_pair(u,v)))continue;
        S.insert(make_pair(u,v));
        DAG.addedge(u,v);
    }
    clr(dp,-1);
    rep(i,1,grpid)dfs(i);
    int ans1=*max_element(dp+1,dp+grpid+1);
    int ans2=0;
    rep(i,1,grpid)if(ans1==dp[i])ans2=(ans2+cnt[i])%x;
    printf("%d\n%d",ans1,ans2);
    return 0;
}