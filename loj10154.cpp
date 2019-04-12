/**
* Number:loj10154
* Title:「一本通 5.2 例 2」选课 
* Status:AC
* Tag:[记忆化搜索]
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
}edges[220];
int head[110],nxt[220],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int w[110];
int dp[110][110];
bool vis[110][110];
int dfs(int eid, int m)
{
    if(eid==-1 || m<=0)return 0;
    int u=edges[eid].to;
    if(vis[u][m])return dp[u][m];
    int& ans=dp[u][m];
    ans=0;
    for(int i=0;i<m;i++)
    {
        ans=max(ans, dfs(head[u], i) + dfs(nxt[eid], m-i-1));
    }
    ans+=w[u];
    ans=max(ans, dfs(nxt[eid], m));
    vis[u][m]=true;
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    mset(head,-1);
    rep(i,1,n)
    {
        int pre; readi(pre,w[i]);
        add_edge(pre,i);
    }
    printf("%d",dfs(head[0],m));
    return 0;
}