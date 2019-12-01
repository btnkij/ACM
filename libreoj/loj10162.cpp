/**
* Number:loj10162
* Title:「一本通 5.2 练习 5」骑士
* Status:AC
* Tag:[树型dp]
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
typedef unsigned long long ull;

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

inline int readu()
{
    int num = 0;
    char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

struct Edge
{
    int from,to;
}edges[1000010*2];
int head[1000010],nxt[1000010*2],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int fa[1000010];
int findr(int x)
{
    return x==fa[x]?x:fa[x]=findr(fa[x]);
}
bool merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx==ry)return false;
    fa[rx]=ry;
    return true;
}

ll w[1000010];
vector<Edge> cycle;
int del;
ll dp[1000010][2];
void dfs_help(int u,int pre)
{
    dp[u][0]=0;
    dp[u][1]=w[u];
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs_help(v,u);
        dp[u][0]+=max(dp[v][0], dp[v][1]);
        dp[u][1]+=dp[v][0];
    }
    if(u==del)dp[u][1]=-INF;
}
ll dfs(int u,int _del)
{
    del=_del;
    dfs_help(u,-1);
    return max(dp[u][0], dp[u][1]);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)fa[i]=i,head[i]=-1;
    rep(i,1,n)
    {
        w[i]=readu();
        int v=readu();
        if(merge(i,v))
        {
            add_edge(i,v); add_edge(v,i);
        }
        else
        {
            cycle.push_back((Edge){i,v});
        }
    }
    ll ans=0;
    for(Edge& e:cycle)
    {
        ans+=max(dfs(e.from, e.to), dfs(e.to, e.from));
    }
    printf("%lld",ans);
    return 0;
}