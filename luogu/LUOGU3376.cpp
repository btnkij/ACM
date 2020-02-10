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

/*
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
    printf("%d\n", isap(n, s, t));
    return 0;
}