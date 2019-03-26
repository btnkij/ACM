/**
 * 
 * LCA 最小公共祖先
 * 
**/

#include <cstring>

typedef int ll;

const int MAXN = 1e5 + 10;
const int MAXM = MAXN * 2;
const int LOGN = 17;

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
};

struct lca
{
    directed_graph* G;
    int tin[MAXN], tout[MAXN], timer;
    int fa[MAXN][LOGN]; // fa[i][j]: i的(1<<j)级祖先
    int dis[MAXN]; // dis[i]: i到根结点的距离
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
};