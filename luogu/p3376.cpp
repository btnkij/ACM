/**
* Number:p3376
* Title:网络最大流
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
} G;

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
        int a, b, f;
        readi3(a, b, f);
        solver.add_edge(a, b, f);
    }
    printf("%d\n", solver(s, t));
    return 0;
}

/*
struct dinic
{
    int src, dst;
    directed_graph *G;
    int dep[10010];
    int cur[10010];
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
            for (int i = G->head[u]; ~i; i = G->edges[i].nxt)
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
        for (int &i = cur[u]; ~i; i = G->edges[i].nxt)
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
        int a, b, f;
        readi3(a, b, f);
        solver.add_edge(a, b, f);
    }
    printf("%d\n", solver(s, t));
    return 0;
}
*/