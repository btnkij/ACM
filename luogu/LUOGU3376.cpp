/**
* Number:luogu3376
* Title:网络最大流
* Status:AC
* Tag:[网络流最大流]
* desc: 网络流最大流模板题
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

const int MAXN = 10010;
const int MAXM = 200010;
struct Edge
{
    int from, to, flow, nxt; // 起点，终点，容量
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int flow)
{
    edges[edgeid] = (Edge){from, to, flow, head[from]};
    head[from] = edgeid++;
}
void addflow(int from, int to, int flow)
{
    addedge(from, to, flow);
    addedge(to, from, 0);
}

int h[MAXN], w[MAXN], gap[MAXN * 2];
bool vis[MAXN];
queue<int> Q;
priority_queue<pair<int, int>> P; // first-标号 second-节点编号
inline bool bfs(int n, int src, int dst)
{
    fill_n(h, n + 1, INF), h[dst] = 0;
    Q.push(dst);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i ^ 1];
            if (e.flow > 0 && h[e.from] == INF)
            {
                h[e.from] = h[u] + 1;
                Q.push(e.from);
            }
        }
    }
    h[src] = max(h[src], n); // 源点的标号设为n
    return h[src] != INF;    // 残量网络是否连通
}
inline void relabel(int u) // 重新标号
{
    int tmp = INF;
    for (int i = head[u]; ~i; i = edges[i].nxt)
        if (edges[i].flow > 0)
            tmp = min(tmp, h[edges[i].to]);
    h[u] = tmp + 1;
}
inline void discharge(int u, int src) // 推流
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (e.flow == 0 || u != src && h[u] != h[e.to] + 1)
            continue;
        int f = e.flow;
        if (u != src && w[u] < f) // 源点流量为无穷大，需特殊处理
            f = w[u];
        e.flow -= f, edges[i ^ 1].flow += f;
        w[u] -= f, w[e.to] += f;
        if (!vis[e.to])
        {
            P.emplace(h[e.to], e.to);
            vis[e.to] = true;
        }
        if (u != src && w[u] == 0)
            break;
    }
}
int hlpp(int n, int src, int dst)
{
    if (!bfs(n, src, dst)) // 标号优化：初始标号设置为到汇点的距离
        return 0;
    fill_n(gap, 2 * n, 0); // GAP优化
    for (int i = 1; i <= n; i++)
        if (h[i] != INF)
            ++gap[h[i]];
    vis[src] = vis[dst] = true;
    discharge(src, src);
    while (!P.empty())
    {
        int u = P.top().second;
        P.pop();
        vis[u] = false;
        discharge(u, src);
        if (w[u] > 0)
        {
            if (--gap[h[u]] == 0)
                for (int i = 1; i <= n; i++)
                    if (i != src && i != dst && h[i] > h[u] && h[i] < n + 1)
                        h[i] = n + 1;
            relabel(u);
            ++gap[h[u]];
            P.emplace(h[u], u);
            vis[u] = true;
        }
    }
    return w[dst]; // 返回最大流
}

/*// ISAP
int dep[MAXN], cur[MAXN], num[MAXN], pre[MAXN];
void bfs(int n, int dst)
{
    queue<int> Q;
    fill_n(dep, n + 1, n);
    dep[dst] = 0;
    Q.push(dst);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i ^ 1];
            if (dep[e.from] < n || e.flow <= 0) continue;
            dep[e.from] = dep[u] + 1;
            Q.push(e.from);
        }
    }
}
int augment(int src, int dst)
{
    int f = INF;
    for (int u = dst; u != src; u = edges[pre[u]].from)
        f = min(f, edges[pre[u]].flow);
    for (int u = dst; u != src; u = edges[pre[u]].from)
    {
        edges[pre[u]].flow -= f;
        edges[pre[u] ^ 1].flow += f;
    }
    return f;
}
int isap(int n, int src, int dst)
{
    fill_n(num, n + 1, 0);
    bfs(n, dst);
    for (int i = 1; i <= n; i++)
    {
        num[dep[i]]++;
        cur[i] = head[i];
    }
    int u = src;
    int ans = 0;
    while (dep[src] < n)
    {
        if (u == dst)
        {
            ans += augment(src, dst);
            u = src;
            continue;
        }
        bool found = false;
        for (int &i = cur[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dep[e.to] + 1 != dep[u] || e.flow <= 0) continue;
            found = true;
            u = e.to;
            pre[u] = i;
            break;
        }
        if (!found)
        {
            int mindep = n - 1;
            for (int i = head[u]; ~i; i = edges[i].nxt)
            {
                Edge &e = edges[i];
                if (e.flow > 0) mindep = min(mindep, dep[e.to]);
            }
            if (--num[dep[u]] == 0) break;
            num[dep[u] = mindep + 1]++;
            cur[u] = head[u];
            if (u != src) u = edges[pre[u]].from;
        }
    }
    return ans;
}
*/

/* // Dinic
int dep[MAXN], cur[MAXN]; // 分层，当前弧
bool bfs(int src, int dst)
{
    memset(dep, 0, sizeof(dep));
    dep[src] = 1;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dep[e.to] || e.flow <= 0) continue;
            dep[e.to] = dep[u] + 1;
            Q.push(e.to);
        }
    }
    return dep[dst] > 0;
}
int dfs(int u, int dst, int flow)
{
    if (u == dst) return flow;
    for (int &i = cur[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (dep[e.to] != dep[u] + 1 || e.flow <= 0) continue;
        int f = dfs(e.to, dst, min(flow, e.flow));
        if (f)
        {
            e.flow -= f;
            edges[i ^ 1].flow += f;
            return f;
        }
    }
    return 0;
}
int dinic(int n, int src, int dst)
{
    int ans = 0, f;
    while (bfs(src, dst))
    {
        copy(head, head + n + 1, cur);
        while (f = dfs(src, dst, INF)) ans += f;
    }
    return ans;
}
*/

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
        int a, b, f; readi(a, b, f); // 起点，终点，容量
        addflow(a, b, f);
    }
    // printf("%d\n", dinic(n, s, t));
    // printf("%d\n", isap(n, s, t));
    printf("%d\n", hlpp(n, s, t));
    return 0;
}