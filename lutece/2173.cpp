/**
* Number:2173
* Title:oy环游世界
* Status:AC
* Tag:[状压dp, 记忆化搜索]
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

#define INF 0x3f3f3f3f3f3f3f3f
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

ll adj[20][20];
ll x[20],y[20];
ll dp[20][1<<20];
bool vis[20][1<<20];
ll dfs(int u,int S)
{
    if(vis[u][S])return dp[u][S];
    ll tmp=INF;
    for(int i=1;(1<<i)<=S;i++)
    {
        if(S&(1<<i))
            tmp=min(tmp, adj[u][i]+dfs(i,S^(1<<i)));
    }
    vis[u][S]=true;
    return dp[u][S]=tmp;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,s; readi(n,s);
    rep(i,1,n)
    {
        scanf("%lld %lld",&x[i],&y[i]);
        vis[i][0]=true;
        dp[i][0]=0;
    }
    rep2(i,1,n,j,1,n)adj[i][j]=abs(x[i]-x[j])+abs(y[i]-y[j]);
    ll ans=dfs(s,((1<<n)-1)<<1^(1<<s));
    printf("%lld",ans);
    return 0;
}