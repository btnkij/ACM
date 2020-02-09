/**
* Number:luogu3388
* Title:【模板】割点（割顶）
* Status:AC
* Tag:[tarjan, 割点]
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

const int MAXN = 2e4 + 10;
const int MAXM = 1e5 + 10;
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

bool cut[MAXN];
int dfn[MAXN], low[MAXN], dfsid;
void tarjan(int u, int pre)
{
    dfn[u] = low[u] = ++dfsid;
    int son = 0;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre)
            continue;
        if (!dfn[v])
        {
            son++;
            tarjan(v, u);
            if (low[v] >= dfn[u])
                cut[u] = true;
        }
        low[u] = min(low[u], low[v]);
    }
    if (pre == 0 && son < 2) // 如果是根节点并且连通分量小于2
        cut[u] = false;      // 则根节点不是割点
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
    rep(i, 1, n) if (!dfn[i]) tarjan(i, 0);
    printf("%d\n", count(cut + 1, cut + n + 1, true));
    rep(i, 1, n) if (cut[i]) printf("%d ", i);
    return 0;
}