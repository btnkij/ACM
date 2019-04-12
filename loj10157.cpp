/**
* Number:loj10157
* Title:「一本通 5.2 例 5」皇宫看守 
* Status:AC
* Tag:[树型dp, 点覆盖]
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
}edges[1600*2];
int head[1600],nxt[1600*2],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int w[1600];
int dp[1600][3];
void dfs(int u,int pre)
{
    dp[u][0]=w[u];
    dp[u][1]=INF;
    bool leaf=true;
    int sum=0;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        leaf=false;
        dfs(v, u);
        dp[u][0]+=min(dp[v][0], min(dp[v][1], dp[v][2]));
        dp[u][2]+=min(dp[v][0],dp[v][1]);
        sum+=min(dp[v][0], dp[v][1]);
    }
    if(leaf)return;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dp[u][1]=min(dp[u][1], sum+dp[v][0]-min(dp[v][0],dp[v][1]));
    }
    // printf("u %d pre %d\n",u,pre);
    // printf("%d %d %d\n",dp[u][0],dp[u][1],dp[u][2]);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)head[i]=-1;
    rep(i,1,n)
    {
        int u,k,m; readi(u,k,m);
        w[u]=k;
        rep(j,1,m)
        {
            int v; readi(v);
            add_edge(u,v); add_edge(v,u);
        }
    }
    dfs(1,-1);
    printf("%d", min(dp[1][0], dp[1][1]));
    return 0;
}