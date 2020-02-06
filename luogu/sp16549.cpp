/**
* Number:sp16549
* Title:QTREE6 - Query on a tree VI
* Status:AC
* Tag:[LCT]
* desc: 树上有黑白两色点，询问节点的同色连通块大小
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

struct Node
{
    int fa, son[2];
    int sz, szi; // 实儿子数量，虚儿子数量
};
struct LCT
{
    Node tree[MAXN];
    inline void pushup(int u)
    {
        int l = tree[u].son[0], r = tree[u].son[1];
        tree[u].sz = tree[l].sz + tree[r].sz + tree[u].szi + 1;
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
            tree[u].szi -= tree[rson].sz; // 维护虚儿子信息
            tree[u].szi += tree[tree[u].son[1]].sz;
            tree[u].son[1] = rson;
            pushup(u);
        }
    }
    int findroot(int u)
    {
        access(u);
        splay(u);
        while (tree[u].son[0])
            u = tree[u].son[0];
        return u;
    }
    void link(int x, int y) // 连有向边，y为父节点
    {                       // 维护的是有根树，不能使用makeroot，注意写法上的区别
        access(y), splay(y), splay(x);
        tree[x].fa = y;
        tree[y].szi += tree[x].sz; // 维护y的虚儿子信息
        pushup(y);
    }
    void cut(int x, int y) // 删有向边，y为父节点
    {
        access(x), splay(y);
        tree[y].son[1] = tree[x].fa = 0;
        pushup(y);
    }
} lct[2]; // lct[0]维护黑点组成的动态树，lct[1]维护白点的

int color[MAXN], fa[MAXN];
void dfs(int u, int pre)
{
    fa[u] = pre;
    lct[0].link(u, pre); // lct[0]中，u与父节点有边，表示u为黑色
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre)
            continue;
        dfs(v, u);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n); // 节点数
    rep(i, 1, n + 1) lct[0].tree[i].sz = lct[1].tree[i].sz = 1;
    clr(head, -1), edgeid = 0;
    repne(i, 1, n)
    {
        int u, v;
        readi(u, v);
        addedge(u, v), addedge(v, u);
    }
    dfs(1, n + 1); // 规定根节点1的父节点为(n+1)
    int q;
    readi(q); // 询问数
    while (q--)
    {
        int op, x;
        readi(op, x);
        if (op == 0)
        {
            int c = color[x];
            int r = lct[c].findroot(x);
            lct[c].splay(r);
            printf("%d\n", lct[c].tree[lct[c].tree[r].son[1]].sz);
        }
        else if (op == 1)
        {
            lct[color[x]].cut(x, fa[x]);
            lct[color[x] ^= 1].link(x, fa[x]);
        }
    }
    return 0;
}