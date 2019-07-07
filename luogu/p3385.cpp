/**
* Number:p3385
* Title:负环
* Status:AC
* Tag:[spfa]
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
    } edges[6010];
    int head[2010];
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

struct spfa
{
    directed_graph *G;
    ll dis[2010];
    bool vis[2010];
    int cnt[2010];
    bool operator()(int src)
    {
        memset(dis + 1, INF, sizeof(ll) * G->n_node);
        memset(vis + 1, false, sizeof(bool) * G->n_node);
        memset(cnt + 1, 0, sizeof(int) * G->n_node);
        dis[src] = 0;
        queue<int> Q;
        Q.push(src);
        vis[src] = true;
        cnt[src] = 1;
        while (!Q.empty())
        {
            int cur = Q.front();
            Q.pop();
            vis[cur] = false;
            for (int i = G->head[cur]; ~i; i = G->edges[i].nxt)
            {
                directed_graph::edge &e = G->edges[i];
                if (dis[cur] + e.weight < dis[e.to])
                {
                    dis[e.to] = dis[cur] + e.weight;
                    if (!vis[e.to])
                    {
                        if (++cnt[e.to] >= G->n_node)
                            return false; // 存在负环
                        vis[e.to] = true;
                        Q.push(e.to);
                    }
                }
            }
        }
        return true; // 求出最短路
    }
} solver;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T;
    readi(T);
    solver.G = &G;
    while (T--)
    {
        int n, m;
        readi2(n, m);
        G.clear(n);
        while (m--)
        {
            int a, b, w;
            readi3(a, b, w);
            G.add_edge(a, b, w);
            if (w >= 0)
                G.add_edge(b, a, w);
        }
        if (solver(1))
            printf("N0");
        else
            printf("YE5");
        if (T)
            putchar('\n');
    }
    return 0;
}