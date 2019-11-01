/**
* Number:loj10134
* Title:「一本通 4.4 练习 1」Dis 
* Status:AC
* Tag:[lca]
* desc:询问树上任意链的长度
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
#define PI acos(-1)
typedef long long ll;

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 1e4 + 10;
const int MAXM = 2e4 + 10;
const int LOGN = 15;

struct Edge
{
    int from, to, dis, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int dis) // 边的起止节点，长度
{
    edges[edgeid] = (Edge){from, to, dis, head[from]};
    head[from] = edgeid++;
}

int tin[MAXN], tout[MAXN], dfsid; // dfs进入时间，离开时间
int fa[MAXN][LOGN]; // fa[i][j]: i的(1<<j)级祖先
ll dis[MAXN];       // dis[i]: i到根结点的距离
void dfs(int u, int pre)
{
    tin[u] = ++dfsid;
    fa[u][0] = pre;
    for (int i = 1; i < LOGN; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v != pre)
        {
            dis[v] = dis[u] + edges[i].dis;
            dfs(v, u);
        }
    }
    tout[u] = ++dfsid;
}
void init_lca(int root) // lca的预处理
{
    memset(fa, 0, sizeof(fa));
    dfsid = 0;
    dfs(root, 0);
}
bool isAncestor(int fa, int x) // fa是否是x的祖先
{
    return !fa || (tin[fa] <= tin[x] && tout[x] <= tout[fa]);
}
int lca(int x, int y) // 求x、y的最近公共祖先
{
    if (isAncestor(x, y))
        return x;
    if (isAncestor(y, x))
        return y;
    for (int i = LOGN - 1; i >= 0; i--)
        if (!isAncestor(fa[x][i], y))
            x = fa[x][i];
    return fa[x][0];
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
    repne(i, 1, n)
    {
        int u, v, w;
        readi(u, v, w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    init_lca(1);
    while (m--)
    {
        int u, v;
        readi(u, v);
        printf("%d\n", dis[u] + dis[v] - 2 * dis[lca(u, v)]); // u到v的距离
    }
    return 0;
}