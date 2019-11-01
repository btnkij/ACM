/**
 * 
 * 最小生成树 kruskal
 * 
**/

#include <cstring>
#include <algorithm>

typedef int ll;

const int MAXN = 5e3 + 10;
const int MAXM = 2e5 + 10;

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
} G;

struct union_find_set
{
    int fa[MAXN];
    void clear(int n)
    {
        for(int i = 1; i <= n; i++)
            fa[i] = i;
    }
    int find_root(int x)
    {
        return x == fa[x] ? x : fa[x] = find_root(fa[x]);
    }
    bool merge(int x, int y)
    {
        int rx = find_root(x), ry = find_root(y);
        if(rx == ry)return false;
        fa[rx] = ry;
        return true;
    }
};

struct kruskal
{
    union_find_set ufs;
    ll operator()(directed_graph* G)
    {
        std::sort(G->edges, G->edges + G->n_edge);
        ufs.clear(G->n_node);
        int cnt = G->n_node - 1;
        ll ans = 0;
        for(int i = 0; i < G->n_edge; i++)
        {
            directed_graph::edge& e = G->edges[i];
            if(ufs.merge(e.from, e.to))
            {
                ans += e.weight;
                cnt--;
                if(!cnt)return ans;
            }
        }
        return -1;
    }
};


/**
 * 
 * Prim
 * 
**/

#include <queue>

struct
{
    struct HeapNode
    {
        int eid;
        ll weight;
        bool operator<(const HeapNode& rhs)const
        {
            return weight > rhs.weight;
        }
    };
    bool vis[MAXN], tree[MAXM];
    ll operator()(directed_graph* G)
    {
        // memset(vis + 1, false, sizeof(bool) * G->n_node);
        // memset(tree, false, sizeof(bool) * G->n_edge);
        ll ans = 0;
        std::priority_queue<HeapNode> Q;
        vis[1] = true;
        int cnt = 1;
        for(int i = G->head[1]; ~i; i = G->nxt[i])
            Q.push((HeapNode){i, G->edges[i].weight});
        while(!Q.empty())
        {
            int eid = Q.top().eid;
            directed_graph::edge& e = G->edges[eid];
            Q.pop();
            if(vis[e.to])continue;
            vis[e.to] = true;
            tree[eid] = tree[eid ^ 1] = true;
            cnt++;
            ans += e.weight;
            for(int i = G->head[e.to]; ~i; i = G->nxt[i])
                if(!vis[G->edges[i].to])
                    Q.push((HeapNode){i, G->edges[i].weight});
        }
        return cnt == G->n_node ? ans : -1;
    }
};