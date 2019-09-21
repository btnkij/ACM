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
typedef int ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
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
    } edges[200000];
    int nxt[200000];
    int head[400];
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
}G;

struct mcmf
{
    int src, dst;
    directed_graph *G;
    int flow[200000];
    int pre[400];
    bool vis[400];
    int dis[400];
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
}solver;

int a[400],b[400];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solver.G=&G;
    int n;
    while(readi(n)!=EOF && n)
    {
        G.clear(n+10);
        int p1=n+1,p2=n+2;
        int src=n+3,dst=n+4;
        rep(i,1,n)
        {
            readi(a[i],b[i]);
            solver.add_edge(src,i,1,0);
            solver.add_edge(i,p1,1,-a[i]);
            solver.add_edge(i,p2,1,-b[i]);
        }
        solver.add_edge(p1,dst,8,0);
        solver.add_edge(p2,dst,8,0);
        solver(src,dst);
        printf("%d\n",-solver.mincost);
        rep(u,1,n)
        {
            for(int i=G.head[u];~i;i=G.nxt[i])
            {
                if(i&1)continue;
                directed_graph::edge& e=G.edges[i];
                if(e.to==src)continue;
                if(solver.flow[i]==0)
                {
                    printf("%d %d %d %d\n",u,a[u],b[u],e.to==p1?1:2);
                }
            }
        }
    }
    return 0;
}