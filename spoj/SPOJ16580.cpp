/**
* Number:sp16580
* Title:QTREE7 - Query on a tree VII
* Status:AC
* Tag:[LCT]
* desc: 树上有黑白两色点，询问节点的同色连通块中的最大点权
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

#define INF 0x7fffffff
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
struct Edge // 链式前向星模板
{
    int from, to, nxt;
} edges[MAXN * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

struct Heap
{
    priority_queue<int> open, close;
    void push(int val)
    {
        open.push(val);
    }
    void pop(int val)
    {
        close.push(val);
    }
    int top()
    {
        while (!close.empty() && open.top() == close.top())
            open.pop(), close.pop();
        return open.size() ? open.top() : -INF;
    }
};

int w[MAXN]; // 节点的权值
struct Node  // 有根树，不需要flip翻转标记
{
    int fa, son[2]; // LCT必要节点信息：fa-父节点 son[]-左右儿子
    int maxw;       // 实节点的最大权值
    Heap maxwi;     // 虚节点的最大权值，注意在access虚实转换时维护
};
struct LCT // LCT维护有根树，注意不能makeroot换根
{
    Node tree[MAXN];
    inline void pushup(int u) // 更新maxw
    {
        Node &nod = tree[u];
        nod.maxw = max(
            max(w[u], nod.maxwi.top()),
            max(tree[nod.son[0]].maxw, tree[nod.son[1]].maxw));
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
            if (rson) // 维护虚儿子的信息
                tree[u].maxwi.pop(tree[rson].maxw);
            if (tree[u].son[1])
                tree[u].maxwi.push(tree[tree[u].son[1]].maxw);
            tree[u].son[1] = rson;
            pushup(u);
        }
    }
    int findroot(int u)
    {
        access(u), splay(u);
        while (tree[u].son[0])
            u = tree[u].son[0];
        return u;
    }
    void link(int x, int y)                 // 连有向边，y为父节点
    {                                       // 维护的是有根树，不能使用makeroot，注意写法上的区别
        access(y), splay(y), splay(x);      // x无父节点，fa一定为空，不需要access
        tree[x].fa = y, tree[y].son[1] = x; // 有向树上可以直接连实边
        pushup(y);
    }
    void cut(int x, int y) // 删有向边，y为父节点
    {
        access(x), splay(y);
        tree[y].son[1] = tree[x].fa = 0;
        pushup(y);
    }
} lct[2]; // lct[0]维护黑点组成的动态树，lct[1]维护白点的

int color[MAXN], fa[MAXN]; // color[]-节点的颜色 fa[]-原树中的父节点
void build(int u, int pre)
{
    fa[u] = pre;
    lct[color[u]].link(u, pre); // 节点的颜色记录在连向父节点的边上
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre)
            continue;
        build(v, u);
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
    clr(head, -1), edgeid = 0;
    repne(i, 1, n)
    {
        int u, v;
        readi(u, v);
        addedge(u, v), addedge(v, u);
    }
    rep(i, 1, n) readi(color[i]); // 读入每个节点的颜色
    rep(i, 1, n) readi(w[i]);     // 读入每个节点的权值
    w[0] = w[n + 1] = -INF;
    rep2(i, 0, 1, j, 0, n + 1) lct[i].tree[j].maxw = w[j];
    build(1, n + 1); // 根据有根树建LCT，规定根节点1的父节点为(n+1)
    int q;
    readi(q); // 询问数
    while (q--)
    {
        int op, u;
        readi(op, u);
        LCT &T = lct[color[u]];
        if (op == 0) // 询问u的同色连通块的最大点权
        {
            int r = T.findroot(u);
            T.splay(r); // 根一定与u不同色，右儿子是答案
            printf("%d\n", T.tree[T.tree[r].son[1]].maxw);
        }
        else if (op == 1) // 切换u的颜色
        {
            T.cut(u, fa[u]);
            lct[color[u] ^= 1].link(u, fa[u]);
        }
        else if (op == 2) // 修改u的权值
        {
            T.access(u), T.splay(u);                  // 将u转到根
            readi(w[u]);                              // 读入新的权值
            T.pushup(u), lct[color[u] ^ 1].pushup(u); // 注意pushup两棵LCT
        }
    }
    return 0;
}