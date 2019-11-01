/**
* Number:luogu3384
* Title:树链剖分
* Status:AC
* Tag:[树链剖分]
* desc: 树链剖分模板题
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

const int MAXN = 1e5 + 10;

struct Edge
{
    int from, to, nxt;
} edges[MAXN << 1];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

struct QTreeNode // 树链剖分
{
    ll val;           // 节点的权值
    int dep, sz, pos; // 深度、秩、在线段树中的位置
    int fa, son, top; // 父节点，重儿子，重链顶端节点
} nodes[MAXN];
int dfsid = 0;
int rpos[MAXN];           // 线段树中i位置对应的节点编号为rpos[i]，与pos互逆
void dfs1(int u, int pre) // u-当前节点 pre-父节点
{
    QTreeNode &cur = nodes[u];
    cur.fa = pre;
    cur.dep = nodes[pre].dep + 1;
    int maxsz = cur.sz = 1;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre)
            continue;
        dfs1(v, u);
        cur.sz += nodes[v].sz;
        if (nodes[v].sz >= maxsz)
        {
            maxsz = nodes[v].sz;
            cur.son = v;
        }
    }
}
void dfs2(int u, int top) // u-当前节点 top-重链顶端节点
{
    QTreeNode &cur = nodes[u];
    cur.pos = ++dfsid, rpos[dfsid] = u;
    cur.top = top;
    if (cur.son)            // 如果不是叶节点
        dfs2(cur.son, top); // 先剖重链
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == cur.fa || v == cur.son)
            continue;
        dfs2(v, v); // 再剖轻链
    }
}

ll mod;
struct SegTreeNode // 线段树
{
    ll sum, lazy; // 区间和，lazy标记
} segtree[MAXN << 2];
void push_up(int p)
{
    segtree[p].sum = (segtree[p << 1].sum + segtree[p << 1 | 1].sum) % mod;
}
void push_down(int p, int lt, int rt)
{
    if (!segtree[p].lazy)
        return;
    int lc = p << 1, rc = lc | 1;
    int mid = (lt + rt) >> 1;
    segtree[lc].sum = (segtree[lc].sum + segtree[p].lazy * (mid - lt + 1)) % mod;
    segtree[lc].lazy = (segtree[lc].lazy + segtree[p].lazy) % mod;
    segtree[rc].sum = (segtree[rc].sum + segtree[p].lazy * (rt - mid)) % mod;
    segtree[rc].lazy = (segtree[rc].lazy + segtree[p].lazy) % mod;
    segtree[p].lazy = 0;
}
void build(int p, int lt, int rt)
{
    if (lt == rt)
    {
        segtree[p].sum = nodes[rpos[lt]].val;
        return;
    }
    int mid = (lt + rt) >> 1;
    build(p << 1, lt, mid);
    build(p << 1 | 1, mid + 1, rt);
    push_up(p);
}
// 线段树区间修改 qlt-区间左边界 qrt-区间右边界 qval-加多少
void add_range(int p, int lt, int rt, int qlt, int qrt, ll qval)
{
    if (qlt <= lt && rt <= qrt)
    {
        segtree[p].sum = (segtree[p].sum + qval * (rt - lt + 1)) % mod;
        segtree[p].lazy = (segtree[p].lazy + qval) % mod;
        return;
    }
    push_down(p, lt, rt);
    int lc = p << 1, rc = lc | 1;
    int mid = (lt + rt) >> 1;
    if (qlt <= mid)
        add_range(lc, lt, mid, qlt, qrt, qval);
    if (mid < qrt)
        add_range(rc, mid + 1, rt, qlt, qrt, qval);
    push_up(p);
}
// 线段树区间查询 qlt-区间左边界 qrt-区间右边界 返回区间和
ll query_range(int p, int lt, int rt, int qlt, int qrt)
{
    if (qlt <= lt && rt <= qrt)
        return segtree[p].sum;
    push_down(p, lt, rt);
    int lc = p << 1, rc = lc | 1;
    int mid = (lt + rt) >> 1;
    ll ans = 0;
    if (qlt <= mid)
        ans = query_range(lc, lt, mid, qlt, qrt);
    if (mid < qrt)
        ans = (ans + query_range(rc, mid + 1, rt, qlt, qrt)) % mod;
    return ans;
}
// 树链修改 n-节点总数 x,y-链的端点 qval-加多少
void add_chain(int n, int x, int y, ll qval)
{
    int topx = nodes[x].top, topy = nodes[y].top;
    while (topx != topy) // 如果不在一条链上
    {
        if (nodes[topx].dep >= nodes[topy].dep)
        {
            add_range(1, 1, n, nodes[topx].pos, nodes[x].pos, qval);
            x = nodes[topx].fa;
            topx = nodes[x].top;
        }
        else
        {
            add_range(1, 1, n, nodes[topy].pos, nodes[y].pos, qval);
            y = nodes[topy].fa;
            topy = nodes[y].top;
        }
    }
    if (nodes[x].dep > nodes[y].dep)
        swap(x, y);
    add_range(1, 1, n, nodes[x].pos, nodes[y].pos, qval);
}
// 树链查询 n-节点总数 x,y-链的端点
ll query_chain(int n, int x, int y)
{
    ll ans = 0;
    int topx = nodes[x].top, topy = nodes[y].top;
    while (topx != topy)
    {
        if (nodes[topx].dep >= nodes[topy].dep)
        {
            ans = (ans + query_range(1, 1, n, nodes[topx].pos, nodes[x].pos)) % mod;
            x = nodes[topx].fa;
            topx = nodes[x].top;
        }
        else
        {
            ans = (ans + query_range(1, 1, n, nodes[topy].pos, nodes[y].pos)) % mod;
            y = nodes[topy].fa;
            topy = nodes[y].top;
        }
    }
    if (nodes[x].dep > nodes[y].dep)
        swap(x, y);
    ans = (ans + query_range(1, 1, n, nodes[x].pos, nodes[y].pos)) % mod;
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, r; // 节点数、询问数、根节点编号
    readi(n, m, r);
    scanf("%lld", &mod); // 取模
    rep(i, 1, n) scanf("%lld", &nodes[i].val);
    clr(head, -1);
    repne(i, 1, n) // 建树
    {
        int x, y;
        readi(x, y);
        addedge(x, y);
        addedge(y, x);
    }
    dfs1(r, 0); // 两遍dfs完成树链剖分
    dfs2(r, r);
    build(1, 1, n); // 建线段树
    while (m--)
    {
        int op;
        readi(op);
        int x, y;
        ll z;
        switch (op)
        {
        case 1: // 从x到y的链节点权值加上z
            readi(x, y);
            scanf("%lld", &z);
            add_chain(n, x, y, z);
            break;
        case 2: // 查询x到y的链的和
            readi(x, y);
            printf("%lld\n", query_chain(n, x, y));
            break;
        case 3: // 以x为根的子树节点权值加z
            readi(x);
            scanf("%lld", &z);
            add_range(1, 1, n, nodes[x].pos, nodes[x].pos + nodes[x].sz - 1, z);
            break;
        case 4: // 查询以x为根节点的子树的节点权值和
            readi(x);
            printf("%lld\n", query_range(1, 1, n, nodes[x].pos, nodes[x].pos + nodes[x].sz - 1));
            break;
        }
    }
    return 0;
}