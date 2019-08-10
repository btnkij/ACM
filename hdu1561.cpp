/**
* Number:hdu1561
* Title:The more, The Better
* Status:AC
* Tag:[dp, 树型依赖背包]
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

struct Edge
{
    int from,to,nxt;
}edges[1000];
int head[400],edge_id;
void addedge(int from,int to)
{
    edges[edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id++;
}
int r[400],dp[400][400],sz[400];
int now;
int dfs(int u,int C)
{
    sz[u]=1;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        dfs(v,C);
        sz[u]+=sz[v];
    }
    now++;
    for(int i=1;i<=C;i++)
    {
        dp[now][i]=max(dp[now-1][i-1]+r[u], dp[now-sz[u]][i]);
    }
    return dp[now][C];
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    while(readi(n,m)!=EOF && (n|m))
    {
        edge_id=0;
        clr(head,-1);
        now=0;
        rep(i,1,n)
        {
            int a,b; readi(a,b);
            addedge(a,i);
            r[i]=b;
        }
        int ans=dfs(0,m+1);
        printf("%d\n",ans);
    }
    return 0;
}