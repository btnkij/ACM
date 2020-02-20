/**
* Number:luogu6113
* Title:【模板】一般图最大匹配
* Status:AC
* Tag:[一般图最大匹配, 带花树]
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

const int MAXN = 1010;
const int MAXM = 5e4 + 10;
struct Edge // 链式前向星模板
{
    int from, to, nxt;
} edges[MAXM * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

int fa[MAXN];
int color[MAXN], pre[MAXN], match[MAXN]; // match[i]-与i匹配的是谁
int Q[MAXN], qhead, qtail;               // 队列，只压入color=1的点
int grp[MAXN], grpid;                    // 奇环缩点后的编号
int findr(int x)                         // 并查集模板
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}
int lca(int x, int y) // 找到x,y在BFS树上的LCA
{                     // 采用标记法，x,y交替往上跳，直到遇到被对方标记过的点
    for (++grpid;; swap(x, y))
    {
        if (!x)
            continue;
        x = findr(x);
        if (grp[x] == grpid)
            return x;
        else
            grp[x] = grpid, x = pre[match[x]];
    }
}
void shrink(int u, int v, int root) // 缩奇环
{
    while (findr(u) != root)
    {
        pre[u] = v, v = match[u];
        if (color[v] == 2)
            color[v] = 1, Q[qtail++] = v; // 如果颜色变为1，压入队列
        fa[u] = fa[v] = root;
        u = pre[v];
    }
}
bool augment(int n, int src) // BFS増广
{
    iota(fa, fa + n + 1, 0);
    fill_n(color, n + 1, 0), fill_n(pre, n + 1, 0);
    color[src] = 1;
    qhead = qtail = 0;
    Q[qtail++] = src;
    for (int u = Q[qhead]; qhead < qtail; u = Q[++qhead])
    {
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].to;
            if (color[v] == 2 || findr(u) == findr(v)) // 如果找到偶环或者被缩为一点
                continue;
            if (!color[v]) // 如果没有访问过
            {
                color[v] = 2;
                pre[v] = u;
                if (!match[v])
                {
                    for (int x = v; x;)
                    {
                        int tmp = match[pre[x]];
                        match[x] = pre[x], match[pre[x]] = x;
                        x = tmp;
                    }
                    return true;
                }
                color[match[v]] = 1;
                Q[qtail++] = match[v];
            }
            else if (color[v] == 1) // 如果找到奇环
            {
                int root = lca(u, v);
                shrink(u, v, root), shrink(v, u, root);
            }
        }
    }
    return false;
}
int blossom(int n) // n-节点数 带花树算法：返回最大匹配数，匹配方案在match[]中
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!match[i])
            ans += augment(n, i);
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m);   // n-节点数 m-边数
    clr(head, -1); // 链式前向星的初始化
    repne(i, 0, m)
    {
        int u, v;
        readi(u, v);
        addedge(u, v), addedge(v, u); // 无向图连边
    }
    int maxmatch = blossom(n);
    printf("%d\n", maxmatch); // 输出最大匹配数
    for (int i = 1; i <= n; i++)
        printf("%d ", match[i]); // 输出匹配方案，未匹配的输出0
    return 0;
}