/**
* Number:loj10098
* Title:「一本通 3.6 例 1」分离的路径
* Status:AC
* Tag:[tarjan, 割边]
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
const int MAXM = 1e4 + 10;
struct Edge
{
    int from, to, nxt;
} edges[MAXM * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

int dfn[MAXN], low[MAXN], dfsid;
int grp[MAXN], grpid;
vector<int> trace;
void tarjan(int u, int pre)
{
    dfn[u] = low[u] = ++dfsid;
    trace.push_back(u);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        if ((i ^ 1) == pre)
            continue; // 不经过反向边，保证求出来的双连通
        int v = edges[i].to;
        if (!dfn[v])
        {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], dfn[v]); // 无向图中DFS，u、v一定在一条链上，不需要if(!grp[v])
    }
    if (dfn[u] == low[u])
    {
        for (grp[u] = ++grpid; trace.back() != u; trace.pop_back())
            grp[trace.back()] = grpid;
        trace.pop_back();
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m);
    clr(head, -1), edgeid = 0;
    while (m--)
    {
        int u, v;
        readi(u, v);
        addedge(u, v), addedge(v, u);
    }
    rep(i, 1, n) if (!dfn[i]) tarjan(i, -1);
    vector<int> deg(grpid + 1, 0); // 记录每个双连通分量的度
    for_each(edges, edges + edgeid, [&](const Edge &e) {
        if (grp[e.from] != grp[e.to])
            deg[grp[e.to]]++;
    });
    int k = count(deg.begin() + 1, deg.end(), 1); // 度为1的双连通分量个数
    printf("%d\n", (k + 1) / 2);                  // 度为1的分量两两连边，如果单一个，它与任意节点连边
    return 0;
}