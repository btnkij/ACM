/**
* Number:hdu1561
* Title:The more, The Better
* Status:AC
* Tag:[dp, 树型依赖背包]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
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

struct Edge
{
    int from, to, nxt;
} edges[1000];
int head[400], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

int r[400], dp[400][400], sz[400];
int dfsid, rdfn[400]; // dfs序为i的节点是rdfn[i]
int dfs(int u)
{
    sz[u] = 1;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        dfs(v);
        sz[u] += sz[v];
    }
    rdfn[++dfsid] = u;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m; // 物品总数，背包容量
    while (readi(n, m) != EOF && (n | m))
    {
        edgeid = 0;
        clr(head, -1);
        rep(i, 1, n)
        {
            int a, b; // a-i依赖于a b-物品的价值
            readi(a, b);
            addedge(a, i);
            r[i] = b;
        }
        dfsid = 0;
        dfs(0); // 所有物品依赖于虚拟物品0
        rep2(i, 1, n + 1, j, 1, m + 1)
        {
            int u = rdfn[i];
            // i - sz[u]: 如果不选u，它的子树都不能选
            dp[i][j] = max(dp[i - 1][j - 1] + r[u], dp[i - sz[u]][j]);
        }
        printf("%d\n", dp[n + 1][m + 1]);
    }
    return 0;
}