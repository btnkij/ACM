/**
* Number:loj10134
* Title:「一本通 4.4 练习 1」Dis 
* Status:AC
* Tag:[lca]
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

const int MAXN = 1e4 + 10;
const int MAXM = 2e4 + 10;
const int LOGN = 15;

struct directed_graph
{
    struct edge
    {
        int from, to;
        ll weight;
        bool operator<(const edge &rhs) const
        {
            return weight < rhs.weight;
        }
    } edges[MAXM];
    int head[MAXN], nxt[MAXM];
    int n_node; // 顶点数
    int n_edge; // 边数
    void clear(int n_node)
    {
        this->n_node = n_node;
        this->n_edge = 0;
        std::memset(head + 1, -1, sizeof(int) * n_node);
    }
    void add_edge(int from, int to, ll weight)
    {
        edge &e = edges[n_edge];
        e.from = from;
        e.to = to;
        e.weight = weight;
        nxt[n_edge] = head[from];
        head[from] = n_edge++;
    }
}G;

struct lca
{
    directed_graph* G;
    int tin[MAXN], tout[MAXN], timer;
    int fa[MAXN][LOGN]; // fa[i][j]: i的(1<<j)级祖先
    ll dis[MAXN]; // dis[i]: i到根结点的距离
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
                dis[v] = dis[u] + G->edges[i].weight;
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
}solver;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    G.clear(n);
    repne(i,1,n)
    {
        int u,v,w; readi(u,v,w);
        G.add_edge(u,v,w); G.add_edge(v,u,w);
    }
    solver.init(&G, 1);
    while(m--)
    {
        int u,v; readi(u,v);
        printf("%d\n",solver.dis[u]+solver.dis[v]-(solver.dis[solver(u,v)]<<1));
    }
    return 0;
}