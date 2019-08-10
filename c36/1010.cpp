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

const ll MOD=1e9+7;
struct Edge
{
    int from, to;
}edges[4010];
int head[2010], nxt[4010], tot;
void addEdge(int from, int to)
{
    Edge& e = edges[tot];
    e.from = from, e.to = to;
    nxt[tot] = head[from];
    head[from] = tot++;
}

int root, sum;
int rk[2010], maxrk;
bool cg[2010];
void getcg(int u, int pre) // 求重心
{
    rk[u] = 1;
    int tmp = -INF;
    for(int i = head[u]; ~i; i = nxt[i])
    {
        int v = edges[i].to;
        if(v == pre || cg[v])continue;
        getcg(v, u);
        tmp = std::max(tmp, rk[v]);
        rk[u] += rk[v];
    }
    tmp = std::max(tmp, sum - rk[u]);
    if(tmp < maxrk)maxrk = tmp, root = u;
}

int n;
ll m;
ll w[2010];
int cur,buf;
ll All[2][4010],C[4010];
int lenAll,lenC;
ll ans;
void dfs(int u,int pre,ll prod)
{
    prod=prod*w[u];
    if(prod>m)return;
    C[lenC++]=prod;
    int cnt=upper_bound(All[cur]+0,All[cur]+lenAll,m/prod*w[root])-All[cur];
    ans=(ans+cnt+1)%MOD;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre || cg[v])continue;
        dfs(v,u,prod);
    }
}
void solve(int u) // 以u为树根，分治求解
{
    cg[u]=true;
    lenAll=lenC=0;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(cg[v])continue;
        lenC=0;
        dfs(v,u,w[u]);
        sort(C,C+lenC);
        lenAll=merge(All[cur],All[cur]+lenAll,C,C+lenC,All[buf])-All[buf];
        swap(cur,buf);
    }
    for(int i = head[u]; ~i; i = nxt[i])
    {
        int v = edges[i].to;
        if(cg[v])continue;
        maxrk = INF, sum = rk[v];
        getcg(v, 0);
        solve(root);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        clr(cg,false);
        clr(head,-1);
        tot=0;
        cur=0,buf=1;
        lenAll=lenC=0;
        scanf("%d %lld",&n,&m);
        rep(i,1,n)scanf("%lld",w+i);
        repne(i,1,n)
        {
            int u,v; readi(u,v);
            addEdge(u,v); addEdge(v,u);
        }
        ans=n;
        maxrk = INF, sum = n;
        getcg(1, 0);
        solve(root);
        printf("%lld\n",ans%MOD);
    }
    return 0;
}