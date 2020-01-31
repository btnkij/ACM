/**
* Number:cf600e
* Title:Lomsat gelral
* Status:AC
* Tag:[DSU-On-Tree]
* desc: 树上每个节点一种颜色，求所有子树中数量最多的颜色，多个颜色最多时输出它们的和
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

const int MAXN = 1e5 + 10;
vector<int> adj[MAXN];  // 邻接表
int c[MAXN], son[MAXN]; // 节点颜色，重儿子

int dfs(int u, int pre) // 树链剖分
{
    int sum = 1, tmp = 0;
    for (int v : adj[u])
    {
        if (v == pre)
            continue;
        int t = dfs(v, u);
        sum += t;
        if (t > tmp)
            tmp = t, son[u] = v;
    }
    return sum;
}

int prior;                        // 重儿子
ll cnt[MAXN], curmax;             // 当前每种颜色的数量，当前最大值
ll sum, ans[MAXN];                // 当前答案，最终答案
void calc(int u, int pre, int op) // 统计颜色数量，op=1表示统计，-1表示清除
{
    cnt[c[u]] += op;
    if (cnt[c[u]] > curmax)
        curmax = cnt[c[u]], sum = c[u];
    else if (cnt[c[u]] == curmax)
        sum += c[u];
    for (int v : adj[u])
        if (v != pre && v != prior)
            calc(v, u, op);
}
void dfs1(int u, int pre, bool rst) // DSU-On-Tree rst表示计算完后是否清空cnt[]
{
    for (int v : adj[u])
        if (v != pre && v != son[u]) // 重儿子的cnt[]已经保留，不用统计
            dfs1(v, u, true);        // 轻儿子算完要清空
    if (son[u])
        dfs1(son[u], u, false); // 重儿子算完保留cnt[]
    prior = son[u];
    calc(u, pre, 1);
    ans[u] = sum;
    if (rst)
    {
        prior = -1;
        calc(u, pre, -1);
        curmax = -INF; // 注意当前最大值也要清空
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    rep(i, 1, n) readi(c[i]);
    repne(i, 1, n)
    {
        int x, y;
        readi(x, y);
        adj[x].push_back(y), adj[y].push_back(x);
    }
    dfs(1, -1);
    dfs1(1, -1, false);
    rep(i, 1, n) printf("%lld ", ans[i]);
    return 0;
}