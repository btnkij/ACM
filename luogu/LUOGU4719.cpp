/**
* Number:luogu4719
* Title:【模板】动态 DP
* Status:AC
* Tag:[动态DP, LCT, 矩阵]
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
struct Edge
{
    int from, to, nxt;
} edges[MAXN * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

struct Matrix
{
    int mat[2][2];
    Matrix operator*(const Matrix &rhs) const
    {
        Matrix ans;
        repne2(i, 0, 2, j, 0, 2)
            ans.mat[i][j] = max(mat[i][0] + rhs.mat[0][j],
                                mat[i][1] + rhs.mat[1][j]);
        return ans;
    }
};

int w[MAXN];
struct Node
{
    int fa, son[2];
    Matrix f, g;
} tree[MAXN];
inline void pushup(int u)
{
    tree[u].f = tree[u].g;
    if (tree[u].son[0]) // 注意乘法不满足交换律，深度浅的节点应在左侧
        tree[u].f = tree[tree[u].son[0]].f * tree[u].f;
    if (tree[u].son[1])
        tree[u].f = tree[u].f * tree[tree[u].son[1]].f;
}
inline int dir(int u)
{
    return tree[tree[u].fa].son[1] == u;
}
inline bool isroot(int u)
{
    int *son = tree[tree[u].fa].son;
    return son[0] != u && son[1] != u;
}
inline void rotate(int u)
{
    int fa = tree[u].fa, dfa = dir(u);
    int ffa = tree[fa].fa, dffa = dir(fa);
    int sub = tree[u].son[dfa ^ 1];
    tree[u].fa = ffa;
    if (!isroot(fa))
        tree[ffa].son[dffa] = u;
    tree[u].son[dfa ^ 1] = fa, tree[fa].fa = u;
    tree[fa].son[dfa] = sub, tree[sub].fa = fa;
    pushup(fa), pushup(u);
}
void splay(int u)
{
    while (!isroot(u))
    {
        int fa = tree[u].fa;
        if (!isroot(fa))
            rotate(dir(u) == dir(fa) ? fa : u);
        rotate(u);
    }
}
void access(int u)
{
    for (int rson = 0; u; rson = u, u = tree[u].fa)
    {
        splay(u);
        auto g = tree[u].g.mat;
        if (rson)
        {
            auto f1 = tree[rson].f.mat;
            g[0][0] = g[0][1] -= max(f1[0][0], f1[1][0]);
            g[1][0] -= f1[0][0];
        }
        if (tree[u].son[1])
        {
            auto f1 = tree[tree[u].son[1]].f.mat;
            g[0][0] = g[0][1] += max(f1[0][0], f1[1][0]);
            g[1][0] += f1[0][0];
        }
        tree[u].son[1] = rson;
        pushup(u);
    }
}
void build(int u, int pre)
{
    tree[u].fa = pre;
    auto g = tree[u].g.mat;
    g[1][0] = w[u], g[1][1] = -INF;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre)
            continue;
        build(v, u);
        auto f1 = tree[v].f.mat;
        g[0][0] = g[0][1] += max(f1[0][0], f1[1][0]);
        g[1][0] += f1[0][0];
    }
    pushup(u);
}
void change(int u, int val)
{
    access(u), splay(u);
    tree[u].g.mat[1][0] += val - w[u];
    w[u] = val;
    pushup(u);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m; // n-节点数 m-询问数
    rep(i, 1, n) cin >> w[i]; // 节点的权值
    clr(head, -1); // 链式前向星初始化
    repne(i, 1, n)
    {
        int u, v;
        cin >> u >> v;
        addedge(u, v), addedge(v, u);
    }
    build(1, 0); // 建立有根LCT
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        change(x, y); // 将节点x的权值改为y
        splay(1); // 节点1无fa，直接splay就可以旋转到LCT的根
        cout << max(tree[1].f.mat[0][0], tree[1].f.mat[1][0]) << '\n';
    }
    return 0;
}