/**
* Number:p2495
* Title:[SDOI2011]消耗战
* Status:AC
* Tag:[虚树, 树型dp, lca]
* desc: 求所有询问点均不能到达根节点的最小割
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

const int MAXN = 251000;
struct Edge
{
    int from, to, dis, nxt;
};
struct Graph
{
    Edge edges[MAXN * 2];
    int head[MAXN], edgeid;
    void init()
    {
        clr(head, -1);
        edgeid = 0;
    }
    void addedge(int from, int to, int dis)
    {
        edges[edgeid] = {from, to, dis, head[from]};
        head[from] = edgeid++;
    }
} G, G1; // G-原树 G1-虚树

// LCA模板
int tin[MAXN], tout[MAXN], fa[MAXN][20], dfsid;
ll cut[MAXN]; // cut[u]表示节点u到根节点路径上边权的最小值
void dfs(int u, int pre)
{
    fa[u][0] = pre;
    tin[u] = ++dfsid;
    for (int i = 1; i < 20; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = G.head[u]; ~i; i = G.edges[i].nxt)
    {
        Edge &e = G.edges[i];
        if (e.to == pre)
            continue;
        cut[e.to] = min((ll)e.dis, cut[u]);
        dfs(e.to, u);
    }
    tout[u] = ++dfsid;
}
bool isAncestor(int x, int y)
{
    return x == 0 || tin[x] <= tin[y] && tout[y] <= tout[x];
}
int lca(int x, int y)
{
    if (isAncestor(x, y))
        return x;
    if (isAncestor(y, x))
        return y;
    for (int i = 19; i >= 0; i--)
        if (!isAncestor(fa[x][i], y))
            x = fa[x][i];
    return fa[x][0];
}

bool q[MAXN];                  // 是否是询问的点
int h[MAXN], trace[MAXN], top; // 询问的点，栈，栈顶
bool cmp(int x, int y)         // 询问点按照DFS序排序
{
    return tin[x] < tin[y];
}
int build(int k) // 建虚树，只保留询问点及它们的LCA
{
    sort(h, h + k, cmp);
    trace[top = 1] = 1; // 保留根节点
    for (int i = 0; i < k; i++)
    {
        if (top == 1)
        {
            trace[++top] = h[i];
            continue;
        }
        int r = lca(trace[top], h[i]);
        for (; top > 1 && tin[trace[top - 1]] >= tin[r]; top--)
            G1.addedge(trace[top - 1], trace[top], cut[trace[top]]);
        if (trace[top] != r)
        {
            G1.addedge(r, trace[top], cut[trace[top]]);
            trace[top] = r;
        }
        trace[++top] = h[i];
    }
    for (; top > 1; top--)
        G1.addedge(trace[top - 1], trace[top], cut[trace[top]]);
    return trace[1]; // 返回虚树的根节点，本题中恒为1
}

ll dp(int u) // 树型DP
{
    ll ans = 0;
    for (int i = G1.head[u]; ~i; i = G1.edges[i].nxt)
    {
        int v = G1.edges[i].to;
        ans += dp(v);
    }
    if (q[u])
        ans = cut[u];
    q[u] = false, G1.head[u] = -1; // O(k)复杂度的清空虚树，注意不要memset
    return min(ans, (ll)cut[u]);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n); // 原树节点个数
    G.init(), G1.init();
    repne(i, 1, n) // n-1条树边
    {
        int u, v, w;
        readi(u, v, w);
        G.addedge(u, v, w), G.addedge(v, u, w);
    }
    clr(cut, INF);
    dfs(1, 0); // LCA预处理
    int m;
    readi(m);
    while (m--)
    {
        int k;
        readi(k); // 询问点个数
        repne(i, 0, k)
        {
            readi(h[i]);    // 读入询问点
            q[h[i]] = true; // 标记询问点
        }
        G1.edgeid = 0;       // 清空虚树的边
        int root = build(k); // 建立虚树
        ll ans = dp(root);   // 树型DP
        printf("%lld\n", ans);
    }
    return 0;
}