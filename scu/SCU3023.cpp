/**
* Number:scu3023
* Title:Network
* Status:AC
* Tag:[lca, 树上差分]
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
typedef int ll;
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

const int MAXN = 1e5 + 10;
const int MAXM = MAXN * 2;
const int LOGN = 17;

struct directed_graph
{
    struct edge
    {
        int from, to;
    } edges[MAXM];
    int head[MAXN], nxt[MAXM];
    int n_node;
    int n_edge;
    void clear(int n_node)
    {
        this->n_node = n_node;
        this->n_edge = 0;
        std::memset(head + 1, -1, sizeof(int) * n_node);
    }
    void add_edge(int from, int to)
    {
        edge &e = edges[n_edge];
        e.from = from;
        e.to = to;
        nxt[n_edge] = head[from];
        head[from] = n_edge++;
    }
}G;

struct
{
    directed_graph* G;
    int tin[MAXN], tout[MAXN], timer;
    int fa[MAXN][LOGN];
    void dfs(int u, int pre)
    {
        tin[u] = timer++;
        fa[u][0] = pre;
        for(int i = 1; i < LOGN; i++)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for(int i = G->head[u]; ~i; i = G->nxt[i])
        {
            int v = G->edges[i].to;
            if(v != pre)
            {
                dfs(v, u);
            }
        }
        tout[u] = timer++;
    }
    void init(directed_graph* G, int root)
    {
        this->G = G;
        memset(fa, 0, sizeof(fa));
        timer = 1;
        dfs(root, 0);
    }
    bool isAncestor(int fa, int x)
    {
        return !fa || (tin[fa] <= tin[x] && tout[x] <= tout[fa]);
    }
    int operator()(int x, int y)
    {
        if(isAncestor(x, y))return x;
        if(isAncestor(y, x))return y;
        for(int i = LOGN - 1; i >= 0; i--)
            if(!isAncestor(fa[x][i], y))
                x = fa[x][i];
        return fa[x][0];
    }
}lca;

int dp[MAXN];
int ans=0;
int n,m;
void dfs(int u,int pre)
{
    for(int i=G.head[u]; ~i; i=G.nxt[i])
    {
        directed_graph::edge& e=G.edges[i];
        if(e.to==pre)continue;
        dfs(e.to, u);
        dp[u]+=dp[e.to];
    }
    if(u!=1)
    {
        if(dp[u]==0)ans+=m;
        else if(dp[u]==1)ans+=1;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n,m)!=EOF && n && m)
    {
        G.clear(n+4);
        repne(i,1,n)
        {
            int u,v;
            readi(u,v);
            G.add_edge(u,v); G.add_edge(v,u);
        }
        lca.init(&G,1);
        mset(dp,0);
        rep(i,1,m)
        {
            int u,v; readi(u,v);
            dp[u]++, dp[v]++, dp[lca(u,v)]-=2;
        }
        ans=0;
        dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}