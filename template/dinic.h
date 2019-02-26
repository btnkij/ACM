/**
 * 
 * 网络流最大流 Dinic
 * 
**/

#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef int ll;
#define INF 0x3f3f3f3f

const int MAXN = 1000 + 20 + 2 + 10;
const int MAXM = (1000 * 20 + 1000 + 20) * 2 + 10;

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
        memset(head + 1, -1, sizeof(int) * n_node);
    }
    void add_edge(int from, int to, int weight)
    {
        edge &e = edges[n_edge];
        e.from = from;
        e.to = to;
        e.weight = weight;
        nxt[n_edge] = head[from];
        head[from] = n_edge++;
    }
};

struct dinic
{
    int src, dst;
    directed_graph *G;
    int dep[MAXN];
    int cur[MAXN];
    void add_edge(int from, int to, int flow)
    {
        G->add_edge(from, to, flow);
        G->add_edge(to, from, 0);
    }
    bool bfs()
    {
        queue<int> Q;
        memset(dep + 1, 0, sizeof(int) * G->n_node);
        dep[src] = 1;
        Q.push(src);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for (int i = G->head[u]; ~i; i = G->nxt[i])
            {
                directed_graph::edge &e = G->edges[i];
                if (dep[e.to] || e.weight <= 0)
                    continue;
                dep[e.to] = dep[u] + 1;
                Q.push(e.to);
            }
        }
        return dep[dst] > 0;
    }
    int dfs(int u, int flow)
    {
        if (u == dst)
            return flow;
        for (int &i = cur[u]; ~i; i = G->nxt[i])
        {
            directed_graph::edge &e = G->edges[i];
            if (dep[e.to] != dep[u] + 1 || e.weight <= 0)
                continue;
            int f = dfs(e.to, min(flow, e.weight));
            if (f)
            {
                e.weight -= f;
                G->edges[i ^ 1].weight += f;
                return f;
            }
        }
        return 0;
    }
    ll operator()(int src, int dst)
    {
        this->src = src;
        this->dst = dst;
        ll ans = 0;
        while (bfs())
        {
            memcpy(cur + 1, G->head + 1, sizeof(int) * G->n_node);
            int f;
            while (f = dfs(src, INF))
                ans += f;
        }
        return ans;
    }
};