/**
* Number:loj10153
* Title:「一本通 5.2 例 1」二叉苹果树 
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
    int from, to, weight;
}edges[220];
int head[110], nxt[220], tot;
void add_edge(int from, int to, ll weight)
{
    Edge &e = edges[tot];
    e.from = from;
    e.to = to;
    e.weight = weight;
    nxt[tot] = head[from];
    head[from] = tot++;
}

int lc[110],rc[110],weight[110];
bool vis[110][110];
int dp[110][110];
int rk[110];
void build(int u, int pre)
{
    rk[u]=1;
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.to==pre)continue;
        build(e.to, u);
        rk[u]+=rk[e.to];
        if(!lc[u])lc[u]=e.to;
        else rc[u]=e.to;
        weight[e.to]=e.weight;
    }
}
int dfs(int u, int q)
{
    if(q==0)return 0;
    else if(q==1)return weight[u];
    if(vis[u][q])return dp[u][q];
    int& ans=dp[u][q];
    int tmp=0;
    if(lc[u])
    {
        repne(i,0,q)
        {
            tmp=max(tmp, dfs(lc[u], min(rk[lc[u]],i)) + dfs(rc[u], min(q-i-1, rk[rc[u]])));
        }
    }
    tmp+=weight[u];
    vis[u][q]=true;
    return ans=tmp;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,q; readi(n,q);
    q++;
    mset(head,-1);
    repne(i,1,n)
    {
        int u,v,w; readi(u,v,w);
        add_edge(u,v,w); add_edge(v,u,w);
    }
    build(1,0);
    printf("%d",dfs(1,q));
    return 0;
}