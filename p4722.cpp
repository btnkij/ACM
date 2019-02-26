/**
* Number:p4722
* Title:最大流 加强版 / 预流推进
* Status:AC
* Tag:[网络流最大流]
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
    } edges[240010];
    int nxt[240010];
    int head[1210];
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

struct hlpp
{
    struct Node
    {
        int id, height;
        ll flow;
    } nodes[1210];
    struct Comparer
    {
        bool operator()(const Node *lhs, const Node *rhs)
        {
            return lhs->height < rhs->height;
        }
    };
    int src, dst;
    directed_graph *G;
    int num[1210 << 1];
    bool vis[1210];
    priority_queue<Node *, vector<Node *>, Comparer> P;
    void add_edge(int from, int to, ll capacity)
    {
        if (capacity <= 0)
            return;
        G->add_edge(from, to, capacity);
        G->add_edge(to, from, 0);
    }
    bool bfs()
    {
        queue<int> Q;
        for (int i = 1; i <= G->n_node; i++)
        {
            nodes[i].id = i;
            nodes[i].flow = 0;
            nodes[i].height = INF;
        }
        nodes[dst].height = 0;
        Q.push(dst);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            int h = nodes[u].height + 1;
            for (int i = G->head[u]; ~i; i = G->nxt[i])
            {
                directed_graph::edge &e = G->edges[i ^ 1];
                if (nodes[e.from].height != INF || e.weight <= 0)
                    continue;
                nodes[e.from].height = h;
                Q.push(e.from);
            }
        }
        if (nodes[src].height == INF)
            return false;
        nodes[src].height = G->n_node;
        return true;
    }
    void discharge(int id)
    {
        for (int i = G->head[id]; ~i; i = G->nxt[i])
        {
            directed_graph::edge &e = G->edges[i];
            if (e.weight <= 0 || id != src && nodes[id].height != nodes[e.to].height + 1)
                continue;
            ll f = e.weight;
            if (id != src && f > nodes[id].flow)
                f = nodes[id].flow;
            e.weight -= f;
            G->edges[i ^ 1].weight += f;
            nodes[id].flow -= f;
            nodes[e.to].flow += f;
            if (!vis[e.to])
            {
                P.push(&nodes[e.to]);
                vis[e.to] = true;
            }
            if (id != src && nodes[id].flow <= 0)
                break;
        }
    }
    void relabel(int id)
    {
        int h = INF;
        for (int i = G->head[id]; ~i; i = G->nxt[i])
            if (G->edges[i].weight > 0)
            {
                h = min(h, nodes[G->edges[i].to].height);
            }
        nodes[id].height = h + 1;
    }
    ll operator()(int src, int dst)
    {
        this->src = src;
        this->dst = dst;
        if (!bfs())
            return 0;
        memset(vis + 1, false, sizeof(bool) * G->n_node);
        vis[src] = vis[dst] = true;
        memset(num, 0, sizeof(int) * (G->n_node << 1));
        for (int i = 1; i <= G->n_node; i++)
            if (nodes[i].height < INF)
                num[nodes[i].height]++;
        P = priority_queue<Node *, vector<Node *>, Comparer>();
        discharge(src);
        while (!P.empty())
        {
            Node *node = P.top();
            P.pop();
            vis[node->id] = false;
            discharge(node->id);
            if (node->flow > 0)
            {
                if (--num[node->height] == 0)
                {
                    for (int i = 1; i <= G->n_node; i++)
                    {
                        if (i == src || i == dst)
                            continue;
                        if (nodes[i].height >= node->height && nodes[i].height < G->n_node + 1)
                        {
                            nodes[i].height = G->n_node + 1;
                        }
                    }
                }
                relabel(node->id);
                num[node->height]++;
                P.push(node);
                vis[node->id] = true;
            }
        }
        return nodes[dst].flow;
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
        int a, b;
        ll f;
        readi2(a, b);
        scanf("%lld", &f);
        solver.add_edge(a, b, f);
    }
    printf("%lld\n", solver(s, t));
    return 0;
}