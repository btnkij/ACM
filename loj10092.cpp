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

const int MAXN=100010;
const int MAXM=1000010;
struct Edge
{
    int from,to,nxt;
}edges[MAXM],dag[MAXM];
int head[MAXN],edge_id,head_dag[MAXN];
void addedge(int head[],Edge edges[],int from,int to)
{
    edges[++edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id;
}

int ord[MAXN],low[MAXN],dfs_id;
int grp[MAXN],grp_id;
int rk[MAXN];
stack<int> trace;
void tarjan(int u)
{
    ord[u]=low[u]=++dfs_id;
    trace.push(u);
    for(int i=head[u];i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!ord[v])tarjan(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(ord[u]!=low[u])return;
    ++grp_id;
    int top;
    do
    {
        top=trace.top(); trace.pop();
        grp[top]=grp_id;
        rk[grp_id]++;
    }while(top!=u);
}

int mod;
bool vis[MAXN];
int dp[MAXN],Maxl[MAXN];
void dfs(int g)
{
    if(vis[g])return;
    vis[g]=true;
    Maxl[g]=rk[g];
    bool leaf=true;
    for(int i=head_dag[g];i;i=dag[i].nxt)
    {
        leaf=false;
        int to=dag[i].to;
        dfs(to);
        if(Maxl[g]==Maxl[to]+rk[g])dp[g]=(dp[g]+dp[to])%mod;
        else if(Maxl[g]<Maxl[to]+rk[g])
        {
            Maxl[g]=Maxl[to]+rk[g];
            dp[g]=dp[to]%mod;
        }
    }
    if(leaf)dp[g]=1;
}

int indeg[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m,mod);
    repne(i,0,m)
    {
        int u,v; readi(u,v);
        addedge(head,edges,u,v);
    }
    rep(u,1,n)if(!ord[u])tarjan(u);
    edge_id=0;
    set<pair<int,int> > S;
    rep(u,1,n)
    {
        for(int i=head[u];i;i=edges[i].nxt)
        {
            int v=edges[i].to;
            if(grp[u]==grp[v] || S.count(pair<int,int>(grp[u],grp[v])))continue;
            S.insert(pair<int,int>(grp[u],grp[v]));
            addedge(head_dag,dag,grp[u],grp[v]);
            indeg[grp[v]]++;
        }
    }
    int ans=0,maxl=-INF;
    rep(g,1,grp_id)
    {
        if(indeg[g])continue;
        dfs(g);
        if(maxl==Maxl[g])ans=(ans+dp[g])%mod;
        else if(maxl<Maxl[g])
        {
            maxl=Maxl[g];
            ans=dp[g];
        }
    }
    printf("%d\n%d",maxl,ans);
    return 0;
}