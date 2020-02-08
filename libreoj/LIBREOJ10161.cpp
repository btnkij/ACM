/**
* Number:loj10161
* Title:「一本通 5.2 练习 4」叶子的染色 
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

struct Edge
{
    int from,to;
}edges[10010*2];
int head[10010],nxt[10010*2],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int n,m;
int dp[10010][2];
void dfs(int u,int pre)
{
    if(u<=m)return;
    dp[u][0]=dp[u][1]=1;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs(v,u);
        dp[u][0]+=min(dp[v][0]-1, dp[v][1]);
        dp[u][1]+=min(dp[v][0], dp[v][1]-1);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    rep(i,1,n)head[i]=-1;
    rep(i,1,m)
    {
        int t; readi(t);
        dp[i][t]=1;
        dp[i][t^1]=INF;
    }
    repne(i,1,n)
    {
        int u,v; readi(u,v);
        add_edge(u,v); add_edge(v,u);
    }
    dfs(m+1,-1);
    printf("%d",min(dp[m+1][0],dp[m+1][1]));
    return 0;
}