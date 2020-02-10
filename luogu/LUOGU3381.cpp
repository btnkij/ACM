/**
* Number:luogu3381
* Title:最小费用最大流
* Status:AC
* Tag:[最小费用最大流]
* desc: 最小费用最大流模板题
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
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 5010;
const int MAXM = 100010;

struct Edge
{
    int from, to, flow, dis, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int flow, int dis)
{
    edges[edgeid] = (Edge){from, to, flow, dis, head[from]};
    head[from] = edgeid++;
}
void addflow(int from, int to, int flow, int dis)
{
    addedge(from, to, flow, dis);
    addedge(to, from, 0, -dis);
}

int dis[MAXN], pre[MAXN]; // 最短路长度，最短路树
bool vis[MAXN];
bool spfa(int n, int src, int dst)
{
    fill_n(dis, n + 1, INF);
    dis[src] = 0;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (e.flow <= 0 || dis[u] + e.dis >= dis[e.to]) continue;
            dis[e.to] = dis[u] + e.dis;
            pre[e.to] = i;
            if (!vis[e.to])
            {
                Q.push(e.to);
                vis[e.to] = true;
            }
        }
    }
    return dis[dst] < INF;
}
int maxflow, mincost; // 最大流，取得最大流的最小费用
void mcmf(int n, int src, int dst)
{
    maxflow = mincost = 0;
    while (spfa(n, src, dst))
    {
        int f = INF;
        for (int u = dst; u != src; u = edges[pre[u]].from)
            f = min(f, edges[pre[u]].flow);
        for (int u = dst; u != src; u = edges[pre[u]].from)
        {
            edges[pre[u]].flow -= f;
            edges[pre[u] ^ 1].flow += f;
            mincost += f * edges[pre[u]].dis;
        }
        maxflow += f;
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, s, t;
    readi(n, m, s, t); // 点数，边数，源点，汇点
    clr(head, -1);
    while (m--)
    {
        int u, v, w, f; readi(u, v, w, f); // 起点，终点，容量，费用
        addflow(u, v, w, f);
    }
    mcmf(n, s, t);
    printf("%d %d", maxflow, mincost);
    return 0;
}