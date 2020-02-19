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

int fa[MAXN];
int color[MAXN], pre[MAXN], match[MAXN];
int Q[MAXM], qhead, qtail;
int grp[MAXN], grpid;
int findr(int x)
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}
int lca(int x, int y)
{
    for (++grpid;; swap(x, y)) if(x)
    {
        x = findr(x);
        if (grp[x] == grpid)
            return x;
        else grp[x] = grpid, x = pre[match[x]];
    }
}
void shrink(int u, int v, int root)
{
    while (findr(u) != root)
    {
        pre[u] = v, v = match[u];
        if (color[v] == 2)
            color[v] = 1, Q[qtail++] = v;
        fa[u] = fa[v] = root;
        u = pre[v];
    }
}
bool augment(int n, int src)
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
            if (color[v] == 2 || findr(u) == findr(v))
                continue;
            if (!color[v])
            {
                color[v] = 2;
                pre[v] = u;
                if (!match[v])
                {
                    for (int x = v; x;)
                    {
                        int tmp=match[pre[x]];
                        match[x] = pre[x], match[pre[x]] = x;
                        x=tmp;
                    }
                    return true;
                }
                color[match[v]] = 1;
                Q[qtail++] = match[v];
            }
            else if(color[v]==1)
            {
                int root = lca(u, v);
                shrink(u, v, root), shrink(v, u, root);
            }
        }
    }
    return false;
}
int blossom(int n)
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
    readi(n, m);
    clr(head, -1);
    repne(i, 0, m)
    {
        int u, v;
        readi(u, v);
        addedge(u, v), addedge(v, u);
    }
    int maxmatch = blossom(n);
    printf("%d\n", maxmatch);
    for (int i = 1; i <= n; i++)
        printf("%d ", match[i]);
    return 0;
}