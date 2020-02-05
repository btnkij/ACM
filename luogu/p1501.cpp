/**
* Number:p1501
* Title:[国家集训队]Tree II
* Status:AC
* Tag:[lct]
* desc: 在动态连边和删边的树上，维护链上的节点权值和
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
const int MOD = 51061;
struct Node
{
    int flip, fa, son[2]; // LCT节点必要的信息：flip-翻转标记 fa-父节点 son[]-左右儿子
    ll val, ans;          // val-节点的值 ans-子树的答案
    ll add, mul;          // add-加法lazy标记 mul-乘法lazy标记
    int sz;               // 子树大小
} tree[MAXN];
inline void pushup(int u) // 计算要维护的信息
{
    int l = tree[u].son[0], r = tree[u].son[1];
    tree[u].sz = tree[l].sz + tree[r].sz + 1;
    tree[u].ans = (tree[l].ans + tree[r].ans + tree[u].val) % MOD;
}
void pushadd(int u, ll lazy) // 传递加法标记
{
    Node &nod = tree[u];
    nod.val = (nod.val + lazy) % MOD;
    nod.ans = (nod.ans + lazy * nod.sz) % MOD;
    nod.add = (nod.add + lazy) % MOD;
}
void pushmul(int u, ll lazy) // 传递乘法标记
{
    Node &nod = tree[u];
    nod.val = (nod.val * lazy) % MOD;
    nod.ans = (nod.ans * lazy) % MOD;
    nod.mul = (nod.mul * lazy) % MOD;
    nod.add = (nod.add * lazy) % MOD;
}
inline void pushdown(int u) // 传递所有标记
{
    Node &nod = tree[u];
    if (nod.flip == 1)
    {
        swap(nod.son[0], nod.son[1]);
        tree[nod.son[0]].flip ^= 1, tree[nod.son[1]].flip ^= 1;
        nod.flip = 0;
    }
    if (nod.mul != 1)
    {
        pushmul(nod.son[0], nod.mul), pushmul(nod.son[1], nod.mul);
        nod.mul = 1;
    }
    if (nod.add != 0)
    {
        pushadd(nod.son[0], nod.add), pushadd(nod.son[1], nod.add);
        nod.add = 0;
    }
}
inline int dir(int u) // 节点u在它父节点的哪一支
{
    return tree[tree[u].fa].son[1] == u;
}
inline bool isroot(int u) // 节点u是否是SplayTree的根节点
{
    int *son = tree[tree[u].fa].son;
    return son[0] != u && son[1] != u;
}
inline void rotate(int u)
{
    int fa = tree[u].fa, dfa = dir(u);
    int ffa = tree[fa].fa, dffa = dir(fa);
    int sub = tree[u].son[dfa ^ 1];
    tree[u].fa = ffa;            // 子-父连边
    if (!isroot(fa))             // 如果fa不是根节点
        tree[ffa].son[dffa] = u; // 连父-子实边，否则只有子-父虚边
    tree[u].son[dfa ^ 1] = fa, tree[fa].fa = u;
    tree[fa].son[dfa] = sub, tree[sub].fa = fa;
    pushup(fa), pushup(u);
}
void splay(int u)
{
    static int up[MAXN];
    int tot = 0;
    for (int x = u;; x = tree[x].fa)
    {
        up[tot++] = x;
        if (isroot(x))
            break;
    }
    while (tot--) // 自顶向下传递标记
        pushdown(up[tot]);
    while (!isroot(u))
    {
        int fa = tree[u].fa;
        if (!isroot(fa))
            rotate(dir(u) == dir(fa) ? fa : u);
        rotate(u);
    }
}
void access(int u) // 使根节点-u的链在一棵SplayTree上，u为最深的节点
{
    for (int rson = 0; u; rson = u, u = tree[u].fa)
    {
        splay(u);
        tree[u].son[1] = rson;
        pushup(u);
    }
}
void makeroot(int u) // 使u成为原树的根节点
{                    // makeroot操作后，u也是SplayTree的根节点，u无左儿子
    access(u);
    splay(u);
    tree[u].flip ^= 1;
}
int findroot(int u) // 返回u在原树中的根节点
{                   // findroot操作后，u为SplayTree的根节点
    access(u);
    splay(u);
    while (true)
    {
        pushdown(u);
        if (!tree[u].son[0])
            return u;
        u = tree[u].son[0];
    }
}
void split(int x, int y) // 计算链x-y的信息，答案为tree[y].ans
{                        // split操作后，根节点y无右儿子，左儿子为以x为根的子树
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x, int y) // 连接x、y两个节点，已连通则无效果
{
    makeroot(x);
    if (findroot(y) != x)
        tree[x].fa = y;
}
void cut(int x, int y) // 断开x、y两个节点，已连通则无效果
{
    split(x, y);
    if (tree[y].son[0] == x)
    {
        tree[x].fa = tree[y].son[0] = 0;
        pushup(y);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, q;
    readi(n, q); // n-节点数 q-询问数
    rep(i, 1, n) tree[i].val = tree[i].ans = tree[i].mul = tree[i].sz = 1;
    repne(i, 1, n)
    {
        int u, v;
        readi(u, v);
        link(u, v); // 连初始边
    }
    while (q--)
    {
        char op[4];
        reads(op);
        if (op[0] == '+') // 链u-v所有节点权值+c
        {
            int u, v, c;
            readi(u, v, c);
            split(u, v);
            pushadd(v, c);
        }
        else if (op[0] == '-') // 删边u1-v1，再加边u2-v2
        {
            int u1, v1, u2, v2;
            readi(u1, v1, u2, v2);
            cut(u1, v1);
            link(u2, v2);
        }
        else if (op[0] == '*') // 链u-v所有节点权值*c
        {
            int u, v, c;
            readi(u, v, c);
            split(u, v);
            pushmul(v, c);
        }
        else if (op[0] == '/') // 询问链u-v节点的权值和
        {
            int u, v;
            readi(u, v);
            split(u, v);
            printf("%lld\n", tree[v].ans);
        }
    }
    return 0;
}