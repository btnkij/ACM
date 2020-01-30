/**
* Number:poj2396
* Title:Budget
* Status:AC
* Tag:[带上下界的可行流]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

const int MAXN = 300;
const int MAXM = 30000;

struct Edge
{
    int from, to, flow, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int flow)
{
    edges[edgeid] = (Edge){from, to, flow, head[from]};
    head[from] = edgeid++;
}
void addflow(int from, int to, int flow)
{
    if (flow == 0)
        return;
    addedge(from, to, flow);
    addedge(to, from, 0);
}

int src, dst, vsrc, vdst;
int lim;
void addflow(int from, int to, int low, int high)
{
    lim += low;
    addflow(from, to, high - low);
    addflow(from, vdst, low);
    addflow(vsrc, to, low);
}
// Dinic模板
int dep[MAXN], cur[MAXN];
bool getdep()
{
    clr(dep, 0);
    dep[vsrc] = 1;
    queue<int> Q;
    Q.push(vsrc);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dep[e.to] || e.flow == 0)
                continue;
            dep[e.to] = dep[u] + 1;
            Q.push(e.to);
        }
    }
    return dep[vdst] > 0;
}
int augment(int u, int flow)
{
    if (u == vdst)
        return flow;
    for (int &i = cur[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (e.flow == 0 || dep[u] + 1 != dep[e.to])
            continue;
        int f = augment(e.to, min(flow, e.flow));
        if (f)
        {
            e.flow -= f, edges[i ^ 1].flow += f;
            return f;
        }
    }
    return 0;
}
int dinic()
{
    int maxflow = 0, f;
    while (getdep())
    {
        memcpy(cur, head, sizeof(head));
        while (f = augment(vsrc, INF))
            maxflow += f;
    }
    return maxflow;
}

int low[210][30], high[210][30];
int ans[210][30];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T;
    readi(T);
    while (T--)
    {
        int n, m;
        readi(n, m);
        src = n + m + 1, dst = src + 1, vsrc = dst + 1, vdst = vsrc + 1;
        int sumr = 0, sumc = 0;
        clr(head, -1);
        edgeid = 0;
        lim = 0;
        rep(i, 1, n)
        {
            int x;
            readi(x);
            sumr += x;
            addflow(src, i, x, x);
        }
        rep(i, 1, m)
        {
            int x;
            readi(x);
            sumc += x;
            addflow(n + i, dst, x, x);
        }
        int c;
        readi(c);
        clr(low, 0);
        clr(high, INF);
        rep(i, 1, c)
        {
            int x, y;
            char con[4];
            int z;
            scanf("%d %d %s %d", &x, &y, con, &z);
            int b1 = x, e1 = x, b2 = y, e2 = y;
            if (x == 0)
                b1 = 1, e1 = n;
            if (y == 0)
                b2 = 1, e2 = m;
            rep2(u, b1, e1, v, b2, e2)
            {
                if (con[0] == '=')
                {
                    low[u][v] = max(low[u][v], z);
                    high[u][v] = min(high[u][v], z);
                }
                else if (con[0] == '<')
                    high[u][v] = min(high[u][v], z - 1);
                else if (con[0] == '>')
                    low[u][v] = max(low[u][v], z + 1);
            }
        }
        bool ok = sumr == sumc;
        rep(u, 1, n)
        {
            if (!ok)
                break;
            rep(v, 1, m)
            {
                if (low[u][v] > high[u][v])
                {
                    ok = false;
                    break;
                }
                addflow(u, n + v, low[u][v], high[u][v]);
            }
        }
        addflow(dst, src, 0, INF);
        if (dinic() != lim)
            ok = false;
        if (ok)
        {
            memcpy(ans, low, sizeof(low));
            for (int i = 1; i < edgeid; i += 2)
            {
                Edge &e = edges[i];
                if (1 <= e.to && e.to <= n && n + 1 <= e.from && e.from <= n + m)
                    ans[e.to][e.from - n] += e.flow;
            }
            rep(u, 1, n)
            {
                rep(v, 1, m) printf("%d ", ans[u][v]);
                printf("\n");
            }
        }
        else
            printf("IMPOSSIBLE\n");
        printf("\n");
    }
    return 0;
}