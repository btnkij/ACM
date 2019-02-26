#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <algorithm>
#include <complex>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#define ll long long
#define INF (1ll << 49ll) + 1ll
#define inf 0x3f3f3f3f
#define re register
#define il inline
using namespace std;
struct edge
{
    int to, next;
    int flow;
} a[2000020];
int head[10010];
int gap[10010];
int h[10010];
int e[10010];
int vis[10010];
int cnt(0);
int n, m, st, ed;
struct cmp
{
    il bool operator()(int xi, int yi) const
    {
        return h[xi] < h[yi];
    }
};
priority_queue<int, vector<int>, cmp> pq;
queue<int> q;
il void addedge(int xi, int yi, int fi)
{
    a[cnt].to = yi;
    a[cnt].next = head[xi];
    a[cnt].flow = fi;
    head[xi] = cnt++;
}
il bool bfs()
{
    re int i;
    memset(h + 1, inf, sizeof(int) * n);
    h[ed] = 0;
    q.push(ed);
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        for (i = head[t]; i != -1; i = a[i].next)
        {
            int v = a[i].to;
            if (a[i ^ 1].flow && h[v] > h[t] + 1)
            {
                h[v] = h[t] + 1;
                q.push(v);
            }
        }
    }
    return h[st] != inf;
}
il void push(int u)
{
    // printf("push %d\n",u);
    re int i;
    for (i = head[u]; i != -1; i = a[i].next)
    {
        int v = a[i].to;
        if ((a[i].flow) && (h[v] + 1 == h[u]))
        {
            int df = min(e[u], a[i].flow);
            a[i].flow -= df;
            a[i ^ 1].flow += df;
            e[u] -= df;
            e[v] += df;
            // printf("%d->%d %d\n",u,v,df);
            if ((v != st) && (v != ed) && (!vis[v]))
            {
                pq.push(v);
                vis[v] = 1;
            }
            if (!e[u])
                break;
        }
    }
}
il void relabel(int u)
{
    re int i;
    h[u] = inf;
    for (i = head[u]; i != -1; i = a[i].next)
    {
        int v = a[i].to;
        if ((a[i].flow))
        {
            if ((h[v] + 1 < h[u]))
                h[u] = h[v] + 1;
            printf("h[%d] %d\n",v,h[v]);
        }
    }
    printf("relabel %d %d\n",u,h[u]);
}
inline int hlpp()
{
    re int i;
    if (!bfs())
        return 0;
    h[st] = n;
    memset(gap, 0, sizeof(int) * (n << 1));
    for (i = 1; i <= n; i++)
        if (h[i] != inf)
            gap[h[i]]++;
    for (i = head[st]; i != -1; i = a[i].next)
    {
        int v = a[i].to;
        if (int f = a[i].flow)
        {
            a[i].flow -= f;
            a[i ^ 1].flow += f;
            e[st] -= f;
            e[v] += f;
            // printf("%d->%d %d\n", st, v, f);
            if (v != st && v != ed && !vis[v])
            {
                pq.push(v);
                vis[v] = 1;
            }
        }
    }
    while (!pq.empty())
    {
        int t = pq.top();
        pq.pop();
        vis[t] = 0;
        push(t);
        if (e[t])
        {
            gap[h[t]]--;
            if (!gap[h[t]])
            {
                for (re int v = 1; v <= n; v++)
                {
                    if (v != st && v != ed && h[v] > h[t] && h[v] < n + 1)
                    {
                        h[v] = n + 1;
                        // printf("gap %d\n", v);
                    }
                }
            }
            relabel(t);
            gap[h[t]]++;
            pq.push(t);
            vis[t] = 1;
        }
    }
    return e[ed];
}
signed main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    re int i;
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &st, &ed);
    for (i = 1; i <= m; i++)
    {
        int x, y;
        ll f;
        scanf("%d%d%lld", &x, &y, &f);
        addedge(x, y, f);
        addedge(y, x, 0);
    }
    ll maxf = hlpp();
    printf("%lld", maxf);
    return 0;
}