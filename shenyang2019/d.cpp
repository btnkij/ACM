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

const ll MOD = 1e9+7;

struct Edge
{
    int from, to, dis;
}edges[20010];
int head[10010], nxt[20010], tot;
void addEdge(int from, int to, int dis)
{
    Edge& e = edges[tot];
    e.from = from, e.to = to, e.dis = dis;
    nxt[tot] = head[from];
    head[from] = tot++;
}

int root, sum;
int rk[10010], maxrk;
bool cg[10010];
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

ll cntall[3],sumall[3],cnt[3],sum1[3],ans[3];
void dfs(int u,int pre,ll x)
{
    cnt[x%3]++;
    sum1[x%3]=(sum1[x%3]+x)%MOD;
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.to==pre || cg[e.to])continue;
        dfs(e.to,u,x+e.dis);
    }
}

void solve(int u) // 以u为树根，分治求解
{
    cg[u]=true;

    clr(cntall,0);
    clr(sumall,0);
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(cg[e.to])continue;
        clr(cnt,0);
        clr(sum1,0);
        dfs(e.to,u,e.dis);
        repne2(i,0,3,j,0,3)
        {
            int k=(i-j+6)%3;
            ans[i]=(ans[i]+sum1[j]*cntall[k]%MOD+sumall[k]*cnt[j]%MOD)%MOD;
        }
        repne(i,0,3)
        {
            ans[i]=(ans[i]+sum1[i])%MOD;
            cntall[i]=(cntall[i]+cnt[i])%MOD;
            sumall[i]=(sumall[i]+sum1[i])%MOD;
        }
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
    int n; // 节点个数
    while(readi(n)!=EOF)
    {
        tot=0;
        clr(head,-1);
        clr(cg,false);
        repne(i,1,n)
        {
            int a,b,c; readi(a,b,c);
            a++,b++;
            addEdge(a,b,c); addEdge(b,a,c);
        }
        clr(ans,0);
        maxrk = INF, sum = n;
        getcg(1, 0);
        solve(root);
        printf("%lld %lld %lld\n",(ans[0]<<1)%MOD,(ans[1]<<1)%MOD,(ans[2]<<1)%MOD);
    }
    return 0;
}