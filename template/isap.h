/**
 * 
 * ISAP 网络流最大流
 * 
**/

#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef int ll;
#define INF 0x3f3f3f3f;

struct directed_graph
{
    struct edge
    {
        int from, to;
        ll weight;
        int nxt;
        bool operator<(const edge &rhs) const
        {
            return weight < rhs.weight;
        }
    } edges[200010];
    int head[10010];
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
        e.nxt = head[from];
        head[from] = n_edge++;
    }
};

struct isap
{
    int src, dst;
    directed_graph *G;
    int dep[10010];
    int cur[10010];
    int num[10010];
    int pre[10010];
    void add_edge(int from, int to, int flow)
    {
        if (flow <= 0)
            return;
        G->add_edge(from, to, flow);
        G->add_edge(to, from, 0);
    }
    void bfs()
    {
        queue<int> Q;
        fill(dep + 1, dep + G->n_node + 1, G->n_node);
        dep[dst] = 0;
        Q.push(dst);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for (int i = G->head[u]; ~i; i = G->edges[i].nxt)
            {
                directed_graph::edge &e = G->edges[i ^ 1];
                if (dep[e.from] < G->n_node || e.weight <= 0)
                    continue;
                dep[e.from] = dep[u] + 1;
                Q.push(e.from);
            }
        }
    }
    ll agument()
    {
        ll f = INF;
        int u = dst;
        while (u != src)
        {
            directed_graph::edge &e = G->edges[pre[u]];
            f = min(f, e.weight);
            u = e.from;
        }
        u = dst;
        while (u != src)
        {
            directed_graph::edge &e = G->edges[pre[u]];
            e.weight -= f;
            G->edges[pre[u] ^ 1].weight += f;
            u = e.from;
        }
        return f;
    }
    ll operator()(int src, int dst)
    {
        this->src = src;
        this->dst = dst;
        memset(num + 1, 0, sizeof(int) * G->n_node);
        bfs();
        for (int i = 1; i <= G->n_node; i++)
        {
            num[dep[i]]++;
            cur[i] = G->head[i];
        }
        int u = src;
        ll ans = 0;
        while (dep[src] < G->n_node)
        {
            if (u == dst)
            {
                ans += agument();
                u = src;
                continue;
            }
            bool found = false;
            for (int &i = cur[u]; ~i; i = G->edges[i].nxt)
            {
                directed_graph::edge &e = G->edges[i];
                if (dep[e.to] + 1 != dep[u] || e.weight <= 0)
                    continue;
                found = true;
                u = e.to;
                pre[u] = i;
                break;
            }
            if (!found)
            {
                int mindep = G->n_node - 1;
                for (int i = G->head[u]; ~i; i = G->edges[i].nxt)
                {
                    directed_graph::edge &e = G->edges[i];
                    if (e.weight > 0)
                        mindep = min(mindep, dep[e.to]);
                }
                if (--num[dep[u]] == 0)
                    break;
                num[dep[u] = mindep + 1]++;
                cur[u] = G->head[u];
                if (u != src)
                    u = G->edges[pre[u]].from;
            }
        }
        return ans;
    }
};