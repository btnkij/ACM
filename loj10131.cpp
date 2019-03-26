/**
* Number:loj10131
* Title:「一本通 4.4 例 2」暗的连锁
* Status:AC
* Tag:[lca, 树型dp]
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
#define PI acos(-1)
typedef long long ll;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to;
}edges[600010];
int head[100010],nxt[600010],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int fa[100010][17];
int tin[100010], tout[100010], timer;
void dfs(int u, int pre)
{
    tin[u]=timer++;
    fa[u][0]=pre;
    for(int i=1;i<17;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.to==pre)continue;
        dfs(e.to, u);
    }
    tout[u]=timer++;
}
bool isAncestor(int fa,int x)
{
    return !fa || tin[fa]<=tin[x] && tout[x]<=tout[fa];
}
int lca(int x,int y)
{
    if(isAncestor(x,y))return x;
    if(isAncestor(y,x))return y;
    for(int i=16;i>=0;i--)
        if(!isAncestor(fa[x][i],y))
            x=fa[x][i];
    return fa[x][0];
}

int cnt[100010];
int dp(int u,int pre)
{
    int& t=cnt[u];
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.to==pre)continue;
        t+=dp(e.to, u);
    }
    return t;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)head[i]=-1;
    repne(i,1,n)
    {
        int a,b; readi(a,b);
        add_edge(a,b); add_edge(b,a);
    }
    dfs(1,0);
    repne(i,0,m)
    {
        int a,b; readi(a,b);
        cnt[a]++, cnt[b]++;
        cnt[lca(a,b)]-=2;
    }
    dp(1,0);
    int ans=0;
    rep(i,2,n)
    {
        if(cnt[i]==1)ans+=1;
        else if(cnt[i]==0)ans+=m;
    }
    printf("%d",ans);
    return 0;
}