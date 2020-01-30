/**
* Number:p3366
* Title:【模板】最小生成树
* Status:AC
* Tag:[mst, 最小生成树, kruskal]
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

const int MAXN = 5e3 + 10;
const int MAXM = 2e5 + 10;
struct Edge
{
    int from, to, w, nxt;
} edges[MAXM * 2]; // 双向边
int head[MAXN], edgeid;
void addedge(int from, int to, int w)
{
    edges[edgeid] = {from, to, w, head[from]};
    head[from] = edgeid++;
}
void addedge2(int u, int v, int w)
{
    addedge(u, v, w);
    addedge(v, u, w);
}

struct HeapNode
{
    int id, dis;
    bool operator<(const HeapNode &rhs) const
    {
        return dis > rhs.dis;
    }
};
bool vis[MAXN];
int prim(int n)
{
    priority_queue<HeapNode> Q;
    for (int i = head[1]; ~i; i = edges[i].nxt)
        Q.push({i, edges[i].w});
    fill_n(vis, n + 1, false), vis[1] = true;
    int cnt = 1, ans = 0;
    while (!Q.empty())
    {
        HeapNode node = Q.top();
        Q.pop();
        int u = edges[node.id].to;
        if (vis[u])
            continue;
        ans += node.dis;
        vis[u] = true, cnt++;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (!vis[e.to])
                Q.push({i, e.w});
        }
    }
    return cnt == n ? ans : -1;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m);
    edgeid = 0, fill_n(head, n + 1, -1);
    rep(i, 1, m)
    {
        int u, v, w;
        readi(u, v, w);
        addedge2(u, v, w);
    }
    int ans = prim(n);
    if (ans != -1)
        printf("%d", ans);
    else
        printf("orz");
    return 0;
}

/**
* Number:p3366
* Title:【模板】最小生成树
* Status:AC
* Tag:[mst, 最小生成树, kruskal]
**/

/*
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

const int MAXN = 5e3 + 10;
const int MAXM = 2e5 + 10;
struct Edge
{
    int u, v, w;
    bool operator<(const Edge &rhs) const
    {
        return w < rhs.w;
    }
} edges[MAXM]; // 无向图

int fa[MAXN]; // 并查集模板
int findr(int x)
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}
bool merge(int x, int y)
{
    int rx = findr(x), ry = findr(y);
    if (rx == ry)
        return false;
    fa[rx] = ry;
    return true;
}

int kruskal(int n, int m) // 有解返回MST的权值，无解返回-1
{
    sort(edges, edges + m);
    int cnt = 1, ans = 0;
    repne(i, 0, m)
    {
        Edge &e = edges[i];
        if (merge(e.u, e.v))
            ans += e.w, cnt++;
    }
    return cnt == n ? ans : -1;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m); // 点数，边数
    repne(i, 0, m) readi(edges[i].u, edges[i].v, edges[i].w);
    iota(fa + 1, fa + n + 1, 1); // 并查集初始化
    int ans = kruskal(n, m);
    if (ans != -1)
        printf("%d", ans);
    else
        printf("orz");
    return 0;
}
*/