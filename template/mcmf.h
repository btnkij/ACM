/**
 * 
 * SPFA 最小费用最大流
 * 
**/

#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef int ll;
#define INF 0x3f3f3f3f

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
    } edges[100010];
    int nxt[100010];
    int head[5010];
    int n_node; // 顶点数
    int n_edge; // 边数
    void clear(int n_node)
    {
        this->n_node = n_node;
        this->n_edge = 0;
        memset(head + 1, -1, sizeof(int) * n_node);
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

struct mcmf
{
    int src, dst;
    directed_graph *G;
    int flow[100010];
    int pre[5010];
    bool vis[5010];
    int dis[5010];
    void add_edge(int from, int to, int capacity, int cost)
    {
        flow[G->n_edge] = capacity;
        G->add_edge(from, to, cost);
        flow[G->n_edge] = 0;
        G->add_edge(to, from, -cost);
    }
    bool spfa()
    {
        memset(dis + 1, INF, sizeof(int) * G->n_node);
        dis[src] = 0;
        queue<int> Q;
        Q.push(src);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            vis[u] = false;
            for (int i = G->head[u]; ~i; i = G->nxt[i])
            {
                int w = G->edges[i].weight, v = G->edges[i].to;
                if (!flow[i] || dis[u] + w >= dis[v])
                    continue;
                dis[v] = dis[u] + w;
                pre[v] = i;
                if (!vis[v])
                {
                    Q.push(v);
                    vis[v] = true;
                }
            }
        }
        return dis[dst] != INF;
    }
    int maxflow, mincost;
    void operator()(int src, int dst)
    {
        this->src = src;
        this->dst = dst;
        maxflow = mincost = 0;
        while (spfa())
        {
            int u = dst;
            int f = INF;
            while (u != src)
            {
                f = min(f, flow[pre[u]]);
                u = G->edges[pre[u]].from;
            }
            maxflow += f;
            u = dst;
            while (u != src)
            {
                directed_graph::edge &e = G->edges[pre[u]];
                flow[pre[u]] -= f;
                flow[pre[u] ^ 1] += f;
                mincost += f * e.weight;
                u = e.from;
            }
        }
    }
};