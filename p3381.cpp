/**
* Number:p3381
* Title:最小费用最大流
* Status:AC
* Tag:[最小费用最大流]
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

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
} G;

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
} solver;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, s, t;
    readi4(n, m, s, t);
    G.clear(n);
    solver.G = &G;
    while (m--)
    {
        int u, v, w, f;
        readi4(u, v, w, f);
        solver.add_edge(u, v, w, f);
    }
    solver(s, t);
    printf("%d %d", solver.maxflow, solver.mincost);
    return 0;
}