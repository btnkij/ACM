/**
* Number:p3387
* Title:【模板】缩点
* Status:AC
* Tag:[tarjan, 缩点, dp]
* desc: 求有向图上一条点权和最大的链
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <unordered_set>
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

const int MAXN = 1e4 + 10;
const int MAXM = 1e5 + 10;
struct Edge
{
    int from, to, nxt;
};
struct Graph
{
    Edge edges[MAXM];
    int head[MAXN], edgeid;
    Graph() // 链式前向星的初始化
    {
        clr(head, -1), edgeid = 0;
    }
    void addedge(int from, int to)
    {
        edges[edgeid] = {from, to, head[from]};
        head[from] = edgeid++;
    }
} G, G1; // G-原图 G1-缩点后的DAG

int w[MAXN], w1[MAXN]; // w[]-原图的点权 w1[]-缩点后的点权
int dfn[MAXN], low[MAXN], dfsid; // dfn[]-DFS序 low[]-可以连接的最小祖先
int grp[MAXN], grpid; // grp[]-缩点后每个节点的连通分量编号
vector<int> trace; // 维护tarjan递归的链
void tarjan(int u)
{
    dfn[u] = low[u] = ++dfsid;
    trace.push_back(u);
    for (int i = G.head[u]; ~i; i = G.edges[i].nxt)
    {
        int v = G.edges[i].to;
        if (!dfn[v])
        {
            tarjan(v); // 如果节点v没有访问，先计算它的low[v]
            low[u] = min(low[u], low[v]);
        }
        else if (!grp[v]) // 如果v没有分组，即在当前的DFS链中
            low[u] = min(low[u], dfn[v]); // 更新最小祖先
    }
    if (dfn[u] == low[u]) // 如果u最小连接到自身，即是连通分量的根
    {
        grp[u] = ++grpid; // trace末尾直到u都属于一个连通分量
        w1[grpid] = w[u];
        while (trace.back() != u)
        {
            grp[trace.back()] = grpid;
            w1[grpid] += w[trace.back()]; // 更新缩点后的权值
            trace.pop_back();
        }
        trace.pop_back();
    }
}

int dp[MAXN];
int dfs(int u) // DAG上的DP
{
    if (~dp[u])
        return dp[u];
    int tmp = 0;
    for (int i = G1.head[u]; ~i; i = G1.edges[i].nxt)
    {
        int v = G1.edges[i].to;
        tmp = max(tmp, dfs(v));
    }
    return dp[u] = w1[u] + tmp;
}

struct pair_hash // 自定义Hash函数
{
    size_t operator()(const pair<int, int> &x) const
    {
        return x.first * MAXN + x.second;
    }
};
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m); // n-节点数 m-边数
    rep(i, 1, n) readi(w[i]); // 节点的权值
    rep(i, 1, m)
    {
        int u, v;
        readi(u, v);
        G.addedge(u, v); // 原图的边
    }
    rep(i, 1, n) if (!dfn[i]) tarjan(i); // 计算强联通分量
    unordered_set<pair<int, int>, pair_hash> vis; // 防止G1中连重边
    repne(i, 0, G.edgeid)
    {
        int u = grp[G.edges[i].from], v = grp[G.edges[i].to];
        if (u != v && !vis.count({u, v}))
        {
            vis.insert({u, v});
            G1.addedge(u, v); // 建立缩点后的图
        }
    }
    int ans = 0;
    clr(dp, -1);
    rep(i, 1, grpid) ans = max(ans, dfs(i));
    printf("%d\n", ans);
    return 0;
}