#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f3f3f3f3fLL
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
struct Edge
{
    int from,to,nxt;
}edges[MAXN<<1];
int head[MAXN],tot;
void addedge(int from,int to)
{
    edges[tot]=(Edge){from,to,head[from]};
    head[from]=tot++;
}

int timer,pos[MAXN],sz[MAXN];
void dfs(int u,int pre)
{
    sz[u]=1;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
    pos[++timer]=u;
}

ll dp[MAXN];
ll a[MAXN],w[MAXN],v[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        tot=0;
        clr(head,-1);
        int n,m; readi(n,m);
        rep(i,1,n)scanf("%lld",w+i);
        rep(i,1,n)scanf("%lld",v+i);
        rep(i,1,n)a[i]=w[i]-v[i];
        rep(i,1,m)
        {
            int u,v; readi(u,v);
            addedge(u,v); addedge(v,u);
        }
        timer=0;
        clr(pos,0);
        rep(i,1,n)if(pos[i]==0)dfs(i,-1);
        dp[0]=-INF;
        for(int i=1;i<=n;i++)
        {
            int u=pos[i];
            dp[i]=max(dp[i-1]+a[u],dp[i-sz[u]]);
        }
        printf("%lld\n",dp[n]);
    }
    return 0;
}