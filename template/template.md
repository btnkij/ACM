[TOC]



### include & define

```c++
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)


int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    return 0;
}
```

### 输入输出优化

```c++
// 读非负int
inline int readu()
{
    register int num = 0;
    register char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ 
        num = (num << 3) + (num << 1) + (ch & 0xF); 
        ch = getchar(); 
    }while('0' <= ch && ch <= '9');
    return num;
}

// 读任意int
inline int read()
{
    register int num = 0;
    register char ch;
    register bool sign = false;
    do
    {
        ch = getchar();
        if(ch == '-')sign = true;
    }while(ch < '0' || ch > '9');
    do{ 
        num = (num << 3) + (num << 1) + (ch & 0xF); 
        ch = getchar(); 
    }while('0' <= ch && ch <= '9');
    if(sign)num = -num;
    return num;
}
```

### 排序

#### 快速排序

```c++
void quick_sort(int* begin, int* end) // 传首尾指针，左闭右开区间
{
    if(end - begin <= 1)return;
    std::swap(*begin, *(begin + rand() % (end - begin)));
    int pivot = *begin;
    int *lt = begin, *rt = end - 1;
    while(lt != rt)
    {
        while(rt != lt && *rt > pivot)rt--;
        if(lt == rt)break;
        *lt = *rt; lt++;
        while(lt != rt && *lt < pivot)lt++;
        if(lt == rt)break;
        *rt = *lt; rt--;
    }
    *lt = pivot;
    quick_sort(begin, lt);
    quick_sort(lt + 1, end);
}
```

#### 归并排序

```c++
void merge_sort(int *begin, int *end) // 传首尾指针，左闭右开区间
{
    static int buffer[100010]; // 保证长度大于待排序的数组
    int L = end - begin;
    if(L <= 1)return;
    int* mid = begin + (L >> 1);
    merge_sort(begin, mid);
    merge_sort(mid, end);
    int* plt = begin;
    int* prt = mid;
    int* pbuf = buffer;
    while(plt != mid && prt != end)
    {
        if(*plt <= *prt)*pbuf = *plt, plt++;
        else *pbuf = *prt, prt++;
        pbuf++;
    }
    if(prt == end)std::copy(plt, mid, begin + (pbuf - buffer));
    std::copy(buffer, pbuf, begin);
}
```



### 依赖背包

```c++
/**
* Number:hdu1561
* Title:The more, The Better
* Status:AC
* Tag:[dp, 树型依赖背包]
**/

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
```

### 数位DP

```c++
/**
* Number:loj10167
* Title:「一本通 5.3 练习 2」不要 62
* Status:AC
* Tag:[数位dp]
* desc: 求[a, b]之间不含"4"和"62"的数的个数
**/

vector<int> num;
int dp[20][20];
int dfs(int dep, int pre, bool bound) // 当前填第几个数字，前一个数字，是否到达上界
{
    if (dep == -1)
        return 1;
    if (!bound && dp[dep][pre] != -1)
        return dp[dep][pre];
    int lim = bound ? num[dep] : 9;
    int ans = 0;
    rep(i, 0, lim)
    {
        if (i == 4 || pre == 6 && i == 2)
            continue;
        ans += dfs(dep - 1, i, bound && i == lim);
    }
    if (!bound)
        dp[dep][pre] = ans;
    return ans;
}
int query(int x)
{
    num.clear();
    for (; x; x /= 10)
        num.push_back(x % 10);
    return dfs(num.size() - 1, 10, true);
}
int main()
{
    int a, b;
    clr(dp, -1);
    while (readi(a, b) != EOF && a && b)
    {
        printf("%d\n", query(b) - query(a - 1));
    }
    return 0;
}
```

### ST表 区间最值查询

```c++
const int MAXN = 1e5 + 10;
const int LOGN = 17;
int mm[MAXN];
int dp[MAXN][LOGN]; // dp[i][0]赋值为为原数组
void init(int n) // 初始化 n-数组长度
{
    for (int i = 2; i <= n; i++)
        mm[i] = i & (i - 1) ? mm[i - 1] : mm[i - 1] + 1;
    for (int k = 1; k < LOGN; k++)
    {
        int L = 1 << k;
        for (int i = 1; i + L - 1 <= n; i++)
            dp[i][k] = std::max(dp[i][k - 1], dp[i + (L >> 1)][k - 1]);
    }
}
ll rmq(int lt, int rt) // 查询区间[lt, rt]的最大值
{
    int k = mm[rt - lt];
    return std::max(dp[lt][k], dp[rt - (1 << k) + 1][k]);
}
```



### 并查集/带权并查集

```c++
/**
* Number:cf688c
* Title:NP-Hard Problem
* Status:AC
* Tag:[并查集, 二分图判定]
* desc: 判定一个图是否是二分图，输出左右支的节点
**/

int fa[100100], rel[100100]; // 父节点，与父节点的关系
int findr(int x)
{
    if (x == fa[x])
        return x;
    int rx = findr(fa[x]);
    rel[x] = rel[x] ^ rel[fa[x]];
    return fa[x] = rx;
}
bool merge(int x, int y, int r)
{
    int rx = findr(x), ry = findr(y);
    if (rx == ry)
        return (rel[x] ^ rel[y]) == r;
    rel[rx] = rel[x] ^ rel[y] ^ r;
    fa[rx] = ry;
    return true;
}

int main()
{
    int n, m;
    readi(n, m);            // 节点数，边数
    rep(i, 1, n) fa[i] = i; // 并查集的初始化
    while (m--)
    {
        int u, v;
        readi(u, v);         // (u, v)无向边
        if (!merge(u, v, 1)) // 合并时出现矛盾
        {
            puts("-1"); // 不是二分图
            return 0;
        }
    }
    rep(i, 1, n) findr(i); // 更新fa[]和rel[]
    int cnt = count(rel + 1, rel + n + 1, 0);
    printf("%d\n", cnt);
    rep(i, 1, n) if (rel[i] == 0) printf("%d ", i); // 左支
    printf("\n%d\n", n - cnt);
    rep(i, 1, n) if (rel[i] == 1) printf("%d ", i); // 右支
    return 0;
}
```

### 树状数组 BIT

```c++
// 一维树状数组
struct binary_indexed_tree
{
    ll data[100010];
    int size; // 最大的下标
    void clear(int size)
    {
        this->size = size;
        memset(data + 1, 0, sizeof(ll) * size);
    }
    // 原数组 arr[idx] += delta
    void add(int idx, ll delta)
    {
        while (idx <= size)
        {
            data[idx] += delta;
            idx += idx & -idx;
        }
    }
    // 查询区间 [1, end] 的和
    ll query_sum(int end)
    {
        ll sum = 0;
        while (end)
        {
            sum += data[end];
            end ^= end & -end;
        }
        return sum;
    }
};

// 二维树状数组
struct binary_indexed_tree_2d
{
    ll data[5010][5010];
    int maxr, maxc; // 最大的下标
    void clear(int maxr, int maxc)
    {
        this->maxr = maxr, this->maxc = maxc;
        for(int i = 0; i <= maxr; i++)
            memset(data[i], 0, sizeof(ll)*maxc);
    }
    // 原数组 arr[r][c] += delta
    void add(int r, int c, ll delta)
    {
        for(int i = r; i <= maxr; i += i & -i)
            for(int j = c; j <= maxc; j += j & -j)
                data[i][j] += delta;
    }
    // 查询区间 [1, 1 : r, c] 的和
    ll query_sum(int r, int c)
    {
        ll sum = 0;
        for(int i = r; i; i ^= i & -i)
            for(int j = c; j; j ^= j & -j)
                sum += data[i][j];
        return sum;
    }
};
```

###  树链剖分+线段树区间操作

```c++
/**
* Number:luogu3384
* Title:树链剖分
* Status:AC
* Tag:[树链剖分, 线段树]
* desc: 树链剖分模板题
**/

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
            printf("%lld\n", 
                   query_range(1, 1, n, nodes[x].pos, nodes[x].pos + nodes[x].sz - 1));
            break;
        }
    }
    return 0;
}
```

### 平衡树

#### Treap

```c++
struct Node
{
    int son[2], size, cnt, prior, val;
    // 左右儿子，子树节点个数，值重复次数，随机权值，值
} tree[10000000];
int nodeid; // 最大节点编号
int makenode(int val)
{
    tree[++nodeid] = (Node){0, 0, 1, 1, rand(), val};
    return nodeid;
}
void maintain(int p)
{
    Node &m = tree[p], &l = tree[m.son[0]], &r = tree[m.son[1]];
    m.size = l.size + r.size + m.cnt;
}
void rotate(int &root, int d) // d=0左旋, d=1右旋
{
    int p = tree[root].son[d ^ 1];
    tree[root].son[d ^ 1] = tree[p].son[d];
    tree[p].son[d] = root;
    maintain(root);
    maintain(p);
    root = p;
}
// 插入val，root为根节点，插入操作会更新根节点
void insert(int &root, int val)
{
    if (root == 0) // 如果平衡树为空
        root = makenode(val);
    else if (tree[root].val == val)
        tree[root].size++, tree[root].cnt++;
    else
    {
        int d = (int)(val > tree[root].val);
        int &branch = tree[root].son[d];
        insert(branch, val);
        if (tree[root].prior < tree[branch].prior)
            rotate(root, d ^ 1);
        maintain(root);
    }
}
// 删除val，root为根节点，删除操作会更新根节点
void remove(int &root, int val)
{
    if (root == 0)
        return;
    else if (tree[root].val == val)
    {
        int l = tree[root].son[0], r = tree[root].son[1];
        if (!l && !r)
        {
            tree[root].size--, tree[root].cnt--;
            if (tree[root].cnt == 0)
                root = 0;
        }
        else if (l && r)
        {
            int d = (int)(tree[l].prior > tree[r].prior);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
        else
        {
            int d = (int)(l > r);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
    }
    else
    {
        int d = tree[root].val < val;
        remove(tree[root].son[d], val);
    }
    maintain(root);
}
// 值val的排名（小于val的数个数+1）
int order(int root, int val)
{
    int ans = 0;
    while (root)
    {
        Node &m = tree[root];
        if (m.val == val)
            return ans + tree[m.son[0]].size;
        if (m.val > val)
            root = m.son[0];
        else
            ans += tree[m.son[0]].size + m.cnt, root = m.son[1];
    }
    return ans;
}
// 查询排序第k的数
int kth(int root, int k)
{
    while (root)
    {
        Node &m = tree[root];
        if (tree[m.son[0]].size >= k)
            root = m.son[0];
        k -= tree[m.son[0]].size;
        if (m.cnt >= k)
            return m.val;
        k -= m.cnt;
        root = m.son[1];
    }
    return 0x7FFFFFFF; // 如果节点没有k个，返回无穷大
}
// 查询val的前驱（最接近val的、严格小于val的数）
int prev(int root, int val)
{
    if (root == 0)
        return -0x7FFFFFFF;
    Node &m = tree[root];
    if (m.val >= val)
        return prev(m.son[0], val);
    return std::max(m.val, prev(m.son[1], val));
}
// 查询val的后继（最接近val的、严格大于val的数）
int nxt(int root, int val)
{
    if (root == 0)
        return 0x7FFFFFFF;
    Node &m = tree[root];
    if (m.val <= val)
        return nxt(m.son[1], val);
    return std::min(m.val, nxt(m.son[0], val));
}
```



### 动态树 LCT

```c++
/**
* Number:p3690
* Title:【模板】Link Cut Tree （动态树）
* Status:AC
* Tag:[lct, 动态树]
* desc: lct模板题，维护链上的异或和
**/

struct Node
{
    int val,sum,flip; // 节点的值、子树的异或和、翻转标记
    int fa,son[2]; // 父节点、左右儿子
}tree[100010];
inline int dir(int u)
{
    return tree[tree[u].fa].son[1]==u;
}
inline void pushup(int u) // 计算要维护的信息
{
    int* son=tree[u].son;
    tree[u].sum=tree[son[0]].sum^tree[son[1]].sum^tree[u].val;
}
inline void pushdown(int u) // 下放翻转标记
{
    if(!tree[u].flip)return;
    int* son=tree[u].son;
    swap(son[0],son[1]);
    tree[u].flip=0;
    tree[son[0]].flip^=1;
    tree[son[1]].flip^=1;
}
inline bool isroot(int u) // 判断u是否是根节点
{
    int* son=tree[tree[u].fa].son;
    return son[0]!=u && son[1]!=u;
}
inline void rotate(int u)
{
    int fa=tree[u].fa, dfa=dir(u);
    int ffa=tree[fa].fa, dffa=dir(fa);
    int sub=tree[u].son[dfa^1];
    tree[u].fa=ffa;
    if(!isroot(fa))tree[ffa].son[dffa]=u; // 两个SplayTree之间连虚边
    tree[u].son[dfa^1]=fa, tree[fa].fa=u;
    tree[fa].son[dfa]=sub, tree[sub].fa=fa;
    pushup(fa); pushup(u);
}
void splay(int u)
{
    static int up[100010];
    int tot=0;
    for(int i=u;;i=tree[i].fa) // 之上而下释放翻转标记
    {
        up[tot++]=i;
        if(isroot(i))break;
    }
    while(tot--)pushdown(up[tot]);
    while(!isroot(u))
    {
        int fa=tree[u].fa;
        if(!isroot(fa))rotate(dir(u)==dir(fa)?fa:u);
        rotate(u);
    }
}
void access(int u) // 使根节点-u的链在一棵SplayTree上，u为最深的节点
{
    for(int rson=0;u;rson=u,u=tree[u].fa)
    {
        splay(u);
        tree[u].son[1]=rson;
        pushup(u);
    }
}
void makeroot(int u) // 使u成为根节点
{
    access(u);
    splay(u);
    tree[u].flip^=1;
}
int findroot(int u) // 返回u的根节点
{
    access(u);
    splay(u);
    while(true)
    {
        pushdown(u);
        if(!tree[u].son[0])return u;
        u=tree[u].son[0];
    }
}
void split(int x,int y) // 计算链x-y的信息，答案为tree[y].sum
{                       // split操作后，y无右儿子，y的左儿子为以x为根的子树
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x,int y) // 连接x, y两个节点
{
    makeroot(x);
    if(findroot(y)!=x)tree[x].fa=y;
}
void cut(int x,int y) // 断开x, y两个节点，不必保证x, y连通
{
    split(x,y);
    if(tree[y].son[0]==x)
    {
        tree[x].fa=tree[y].son[0]=0;
        pushup(y);
    }
}

int main()
{
    int n,m; readi(n,m); // 节点数、询问数
    rep(i,1,n) // 输入每个节点的权值
    {
        readi(tree[i].val);
        tree[i].sum=tree[i].val;
    }
    while(m--)
    {
        int op,x,y; readi(op,x,y);
        if(op==0) // 链x-y的异或和
        {
            split(x,y);
            printf("%d\n",tree[y].sum);
        }
        else if(op==1) // 连接x, y
        {
            link(x,y);
        }
        else if(op==2) // 断开x, y
        {
            cut(x,y);
        }
        else if(op==3) // 将节点x的权值修改为y
        {
            splay(x);
            tree[x].val=y;
            pushup(x);
        }
    }
    return 0;
}
```



### 树套树

```c++
/**
* Number:p3380
* Title:【模板】二逼平衡树（树套树）
* Status:AC
* Tag:[树套树]
**/

// Treap模板
struct Node
{
    // 左右儿子，秩，重复次数，随机权值，值
    int son[2], size, cnt, prior, val;
} tree[10000000];
int nodeid;
int makenode(int val)
{
    tree[++nodeid] = (Node){0, 0, 1, 1, rand(), val};
    return nodeid;
}
void maintain(int p)
{
    Node &m = tree[p], &l = tree[m.son[0]], &r = tree[m.son[1]];
    m.size = l.size + r.size + m.cnt;
}
void rotate(int &root, int d) // d=0左旋, d=1右旋
{
    int p = tree[root].son[d ^ 1];
    tree[root].son[d ^ 1] = tree[p].son[d];
    tree[p].son[d] = root;
    maintain(root);
    maintain(p);
    root = p;
}
void insert(int &root, int val)
{
    if (root == 0)
        root = makenode(val);
    else if (tree[root].val == val)
        tree[root].size++, tree[root].cnt++;
    else
    {
        int d = (int)(val > tree[root].val);
        int &branch = tree[root].son[d];
        insert(branch, val);
        if (tree[root].prior < tree[branch].prior)
            rotate(root, d ^ 1);
        maintain(root);
    }
}
void remove(int &root, int val)
{
    if (root == 0)
        return;
    else if (tree[root].val == val)
    {
        int l = tree[root].son[0], r = tree[root].son[1];
        if (!l && !r)
        {
            tree[root].size--, tree[root].cnt--;
            if (tree[root].cnt == 0)
                root = 0;
        }
        else if (l && r)
        {
            int d = (int)(tree[l].prior > tree[r].prior);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
        else
        {
            int d = (int)(l > r);
            rotate(root, d);
            remove(tree[root].son[d], val);
        }
    }
    else
    {
        int d = tree[root].val < val;
        remove(tree[root].son[d], val);
    }
    maintain(root);
}
int order(int root, int val)
{
    int ans = 0;
    while (root)
    {
        Node &m = tree[root];
        if (m.val == val)
            return ans + tree[m.son[0]].size;
        if (m.val > val)
            root = m.son[0];
        else
            ans += tree[m.son[0]].size + m.cnt, root = m.son[1];
    }
    return ans;
}
int kth(int root, int k)
{
    while (root)
    {
        Node &m = tree[root];
        if (tree[m.son[0]].size >= k)
            root = m.son[0];
        k -= tree[m.son[0]].size;
        if (m.cnt >= k)
            return m.val;
        k -= m.cnt;
        root = m.son[1];
    }
    return 2147483647;
}
int prev(int root, int val)
{
    if (root == 0)
        return -2147483647;
    Node &m = tree[root];
    if (m.val >= val)
        return prev(m.son[0], val);
    return max(m.val, prev(m.son[1], val));
}
int nxt(int root, int val)
{
    if (root == 0)
        return 2147483647;
    Node &m = tree[root];
    if (m.val <= val)
        return nxt(m.son[1], val);
    return min(m.val, nxt(m.son[0], val));
}

int arr[50010];
int seg[50010 << 2]; // 线段树
void build(int p, int l, int r)
{
    for (int i = l; i <= r; i++)
    {
        insert(seg[p], arr[i]);
    }
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}
void update(int p, int l, int r, int qpos, int qval)
{
    remove(seg[p], arr[qpos]);
    insert(seg[p], qval);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (qpos <= mid)
        update(p << 1, l, mid, qpos, qval);
    else
        update(p << 1 | 1, mid + 1, r, qpos, qval);
}
int query_order(int p, int l, int r, int ql, int qr, int qval)
{
    if (ql <= l && r <= qr)
        return order(seg[p], qval);
    int mid = (l + r) >> 1, ans = 0;
    if (ql <= mid)
        ans += query_order(p << 1, l, mid, ql, qr, qval);
    if (mid < qr)
        ans += query_order(p << 1 | 1, mid + 1, r, ql, qr, qval);
    return ans;
}
int query_kth(int l, int r, int ql, int qr, int k)
{
    int low = 0, high = 1e8;
    while (low < high)
    {
        int mid = (low + high + 1) >> 1;
        if (query_order(1, l, r, ql, qr, mid) + 1 > k)
            high = mid - 1;
        else
            low = mid;
    }
    return low;
}
int query_prev(int p, int l, int r, int ql, int qr, int qval)
{
    if (ql <= l && r <= qr)
        return prev(seg[p], qval);
    int mid = (l + r) >> 1, ans = -2147483647;
    if (ql <= mid)
        ans = max(ans, query_prev(p << 1, l, mid, ql, qr, qval));
    if (mid < qr)
        ans = max(ans, query_prev(p << 1 | 1, mid + 1, r, ql, qr, qval));
    return ans;
}
int query_nxt(int p, int l, int r, int ql, int qr, int qval)
{
    if (ql <= l && r <= qr)
        return nxt(seg[p], qval);
    int mid = (l + r) >> 1, ans = 2147483647;
    if (ql <= mid)
        ans = min(ans, query_nxt(p << 1, l, mid, ql, qr, qval));
    if (mid < qr)
        ans = min(ans, query_nxt(p << 1 | 1, mid + 1, r, ql, qr, qval));
    return ans;
}

int main()
{
    srand(time(NULL));
    int n, m;
    readi(n, m); // 序列长度，操作次数
    rep(i, 1, n) readi(arr[i]); // 要维护的序列
    build(1, 1, n);
    while (m--)
    {
        int op;
        readi(op);
        int l, r, k, pos;
        switch (op)
        {
        case 1: // 查询k在区间[l, r]内的排名
            readi(l, r, k);
            printf("%d\n", query_order(1, 1, n, l, r, k) + 1);
            break;
        case 2: // 查询区间[l, r]内排名为k的值
            readi(l, r, k);
            printf("%d\n", query_kth(1, n, l, r, k));
            break;
        case 3: // 修改序列pos位置的值为k
            readi(pos, k);
            update(1, 1, n, pos, k);
            arr[pos] = k;
            break;
        case 4: // 查询k在区间[l, r]内的前驱
            readi(l, r, k);
            printf("%d\n", query_prev(1, 1, n, l, r, k));
            break;
        case 5: // 查询k在区间[l, r]内的后继
            readi(l, r, k);
            printf("%d\n", query_nxt(1, 1, n, l, r, k));
            break;
        }
    }
    return 0;
}
```

### 主席树

```c++
/**
* Number:p3834
* Title:【模板】可持久化线段树 1（主席树）
* Status:AC
* Tag:[可持久化, 主席树, 权值线段树]
* desc: 静态区间第k小
**/

const int MAXN = 2e5 + 10;

struct Node
{
    int sum, lc, rc; // 计数，左右儿子编号
} tree[MAXN * 20]; // 空间复杂度O(nlogn)
int root[MAXN], rootid; // 根节点，版本数量
/*// 建树
void build(int &u, int lt, int rt)
{
    u = ++rootid;
    if (lt == rt)
        return;
    int mid = (lt + rt) >> 1;
    build(tree[u].lc, lt, mid);
    build(tree[u].rc, mid + 1, rt);
}
*/
// 单点修改 pos-修改的位置 u-旧版本的根节点 返回新的根节点
int add(int pos, int u, int lt, int rt)
{
    int id = ++rootid;
    Node &nod = tree[id];
    nod = tree[u]; // 复制节点u
    nod.sum++; // 修改u的副本
    if (lt != rt)
    {
        int mid = (lt + rt) >> 1;
        if (pos <= mid)
            nod.lc = add(pos, nod.lc, lt, mid);
        else
            nod.rc = add(pos, nod.rc, mid + 1, rt);
    }
    return id;
}
// qlt,qrt-查询区间左右端点 lt,rt-当前区间左右端点 k-查询第k小
int query(int qlt, int qrt, int lt, int rt, int k)
{
    if (lt == rt)
        return lt;
    // 区间左儿子的数字个数
    int cnt = tree[tree[qrt].lc].sum - tree[tree[qlt].lc].sum;
    int mid = (lt + rt) >> 1;
    if (cnt >= k) // 如果>=k，查询左儿子
        return query(tree[qlt].lc, tree[qrt].lc, lt, mid, k);
    else // 否则查询右儿子
        return query(tree[qlt].rc, tree[qrt].rc, mid + 1, rt, k - cnt);
}

int a[MAXN], b[MAXN];
int main()
{
    int n, m;
    readi(n, m); // 序列长度，询问数
    repne(i, 0, n)
    {
        readi(a[i]); // 要查询的序列
        b[i] = a[i];
    }
    sort(b, b + n);
    int tot = unique(b, b + n) - b; // 离散化
    repne(i, 0, n)
    {
        int ord = lower_bound(b, b + tot, a[i]) - b + 1;
        root[i + 1] = add(ord, root[i], 1, tot);
    }
    while (m--)
    {
        int lt, rt, k;
        readi(lt, rt, k); // 查询闭区间[lt, rt]的第k小
        printf("%d\n", b[query(root[lt - 1], root[rt], 1, tot, k) - 1]);
    }
    return 0;
}
```

### 可持久化平衡树

```c++
/**
* Number:p3835
* Title:【模板】可持久化平衡树
* Status:AC
* Tag:[可持久化, fhq treap]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <ctime>
using namespace std;

const int MAXN = 1e6 + 10;
struct Node // FhqTreap模板
{
    int son[2], size, cnt, prior, val;
} tree[MAXN * 30];
int node_id;
int clone(int ori)
{
    tree[++node_id] = tree[ori];
    return node_id;
}
int makenode(int val)
{
    tree[++node_id] = (Node){0, 0, 1, 1, rand(), val};
    return node_id;
}
void maintain(int p)
{
    tree[p].size = tree[tree[p].son[0]].size + tree[tree[p].son[1]].size + tree[p].cnt;
}
void split(int val, int p, int &l, int &r)
{
    if (p == 0)
    {
        l = r = 0;
        return;
    }
    int id = clone(p); // 只加这一行代码就可实现可持久化
    if (tree[id].val <= val)
    {
        l = id;
        split(val, tree[id].son[1], tree[l].son[1], r);
    }
    else
    {
        r = id;
        split(val, tree[id].son[0], l, tree[r].son[0]);
    }
    maintain(id);
}
int merge(int l, int r)
{
    if (l == 0 || r == 0)
        return l | r;
    int p;
    if (tree[l].prior < tree[r].prior)
    {
        p = r;
        tree[r].son[0] = merge(l, tree[r].son[0]);
    }
    else
    {
        p = l;
        tree[l].son[1] = merge(tree[l].son[1], r);
    }
    maintain(p);
    return p;
}
void insert(int &root, int val)
{
    int l, m, r;
    split(val, root, l, r);
    split(val - 1, l, l, m);
    if (m)
        tree[m].cnt++, tree[m].size++;
    else
        m = makenode(val);
    root = merge(merge(l, m), r);
}
void remove(int &root, int val)
{
    int l, m, r;
    split(val, root, l, r);
    split(val - 1, l, l, m);
    if (m)
    {
        if (tree[m].cnt == 1)
            m = 0;
        else
            tree[m].cnt--, tree[m].size--;
    }
    root = merge(merge(l, m), r);
}
int order(int &root, int val)
{
    int l, r;
    split(val - 1, root, l, r);
    int ans = tree[l].size + 1;
    root = merge(l, r);
    return ans;
}
int kth(int root, int k)
{
    // if(k>tree[root].size)throw;
    int p = root;
    while (true)
    {
        if (tree[tree[p].son[0]].size >= k)
        {
            p = tree[p].son[0];
            continue;
        }
        k -= tree[tree[p].son[0]].size;
        if (k <= tree[p].cnt)
            return tree[p].val;
        k -= tree[p].cnt;
        p = tree[p].son[1];
    }
}
int prev(int &root, int val)
{
    int l, r, p;
    split(val - 1, root, l, r);
    for (p = l; tree[p].son[1]; p = tree[p].son[1])
        ;
    root = merge(l, r);
    return tree[p].val;
}
int nxt(int &root, int val)
{
    int l, r, p;
    split(val, root, l, r);
    for (p = r; tree[p].son[0]; p = tree[p].son[0])
        ;
    root = merge(l, r);
    return tree[p].val;
}

int root[MAXN], ver;
int main()
{
    srand(233333);
    int n;
    readi(n);
    insert(root[0], -2147483647);
    insert(root[0], 2147483647);
    for (ver = 1; ver <= n; ver++)
    {
        int v, opt, x;
        readi(v, opt, x);
        root[ver] = root[v]; // 在版本v的基础上操作
        switch (opt)
        {
        case 1: // 插入x数
            insert(root[ver], x);
            break;
        case 2: // 删除x数(若有多个相同的数，因只删除一个，如果没有请忽略该操作)
            remove(root[ver], x);
            break;
        case 3: // 查询x数的排名(排名定义为比当前数小的数的个数+1。若有多个相同的数，因输出最小的排名)
            printf("%d\n", order(root[ver], x) - 1);
            break;
        case 4: // 查询排名为x的数
            printf("%d\n", kth(root[ver], x + 1));
            break;
        case 5: // 求x的前驱(前驱定义为小于x，且最大的数，如不存在输出-2147483647)
            printf("%d\n", prev(root[ver], x));
            break;
        case 6: // 求x的后继(后继定义为大于x，且最小的数，如不存在输出2147483647)
            printf("%d\n", nxt(root[ver], x));
            break;
        }
    }
    return 0;
}
```



```c++
/**
* Number:p3835
* Title:【模板】可持久化平衡树
* Status:AC
* Tag:[可持久化线段树, 二分]
**/

const int MAXN=5e5+10;

struct Node
{
    Node *lson,*rson;
    int val;
}tree[MAXN*20];
int node_id;
Node* clone(Node* ori)
{
    tree[++node_id]=*ori;
    return &tree[node_id];
}
Node* update(Node* p,int lt,int rt,int qpos,int qval)
{
    Node* nod=clone(p);
    if(lt==rt)
    {
        nod->val=max(0, nod->val+qval);
        return nod;
    }
    int mid=(lt+rt)>>1;
    if(qpos<=mid)nod->lson=update(nod->lson,lt,mid,qpos,qval);
    else nod->rson=update(nod->rson,mid+1,rt,qpos,qval);
    nod->val=nod->lson->val+nod->rson->val;
}
int query(Node* p,int lt,int rt,int qlt,int qrt)
{
    if(qlt<=lt && rt<=qrt)return p->val;
    int mid=(lt+rt)>>1;
    int sum=0;
    if(qlt<=mid)sum+=query(p->lson,lt,mid,qlt,qrt);
    if(mid<qrt)sum+=query(p->rson,mid+1,rt,qlt,qrt);
    return sum;
}

int v[MAXN],opt[MAXN],x[MAXN],ord[MAXN],tot;
Node* root[MAXN];
void init()
{
    node_id=0;
    tree[0]=(Node){&tree[0],&tree[0],0};
    root[0]=&tree[0];
    root[0]=update(root[0],1,tot-1,1,1);
    root[0]=update(root[0],1,tot-1,tot-1,1);
}
int nth(Node* p,int lt,int rt,int n)
{
    if(lt==rt)return ord[lt];
    int mid=(lt+rt)>>1;
    if(p->lson->val > n)return nth(p->lson,lt,mid,n);
    else return nth(p->rson, mid+1, rt, n - p->lson->val);
}

int main()
{
    int n; readi(n);
    ord[1]=x[1]=-2147483647, ord[n+2]=x[n+2]=2147483647;
    rep(i,1,n)
    {
        readi(v[i],opt[i],x[i+1]);
        ord[i+1]=x[i+1];
    }
    sort(ord+1,ord+n+3);
    tot=unique(ord+1,ord+n+3)-ord;
    init();
    rep(i,1,n)
    {
        int id=lower_bound(ord+1,ord+tot,x[i+1])-ord;
        int k;
        switch(opt[i])
        {
        case 1:
            root[i]=update(root[v[i]],1,tot-1,id,1);
            break;
        case 2:
            root[i]=update(root[v[i]],1,tot-1,id,-1);
            break;
        case 3:
            root[i]=root[v[i]];
            printf("%d\n",query(root[v[i]],1,tot-1,1,id-1));
            break;
        case 4:
            root[i]=root[v[i]];
            printf("%d\n",nth(root[v[i]],1,tot-1,x[i+1]));
            break;
        case 5:
            root[i]=root[v[i]];
            k=query(root[v[i]],1,tot-1,1,id-1);
            printf("%d\n",nth(root[v[i]],1,tot-1,k-1));
            break;
        case 6:
            root[i]=root[v[i]];
            k=query(root[v[i]],1,tot-1,1,id);
            printf("%d\n",nth(root[v[i]],1,tot-1,k));
            break;
        }
    }
    return 0;
}
```

### 左偏树 可并堆

```c++
/**
* Number:p3377
* Title:【模板】左偏树（可并堆）
* Status:AC
* Tag:[左偏树, 可并堆]
* desc: 维护n个小根堆，支持合并堆、删除最小值的操作
**/

const int MAXN = 1e5 + 10;

int val[MAXN], dis[MAXN], fa[MAXN], son[MAXN][2]; // 值，深度，并查集，左右儿子
int findr(int x)
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}
int join(int x, int y) // 合并以x, y为根的堆, x或y作为新的根
{
    if (x == 0 || y == 0)
        return x | y;
    if (val[x] > val[y] || (val[x] == val[y] && x > y))
        swap(x, y);
    son[x][1] = join(son[x][1], y);
    if (dis[son[x][0]] < dis[son[x][1]])
        swap(son[x][0], son[x][1]);
    dis[x] = dis[son[x][1]] + 1;
    return fa[x] = fa[son[x][0]] = fa[son[x][1]] = x;
}
void pop(int x) // 删除节点x, x是堆的根
{
    fa[son[x][0]] = son[x][0];
    fa[son[x][1]] = son[x][1];
    fa[x] = join(son[x][0], son[x][1]);
}

bool del[MAXN]; // 是否被删除
int main()
{
    int n, m;
    readi(n, m);
    dis[0] = -1;
    rep(i, 1, n)
    {
        readi(val[i]);
        fa[i] = i;
    }
    while (m--)
    {
        int op;
        readi(op);
        if (op == 1) // 合并x、y所在的堆
        {
            int x, y;
            readi(x, y);
            if (del[x] || del[y])
                continue;
            int rx = findr(x), ry = findr(y);
            if (rx == ry) // 如果在一个堆中
                continue;
            join(rx, ry);
        }
        else if (op == 2) // 删除x所在堆的最小值
        {
            int x;
            readi(x);
            if (del[x])
                printf("-1\n");
            else
            {
                int rx = findr(x);
                printf("%d\n", val[rx]); // 打印最小值
                del[rx] = true;
                pop(rx); // 删除
            }
        }
    }
    return 0;
}
```

### 最近公共祖先 LCA

```c++
/**
* Number:loj10134
* Title:「一本通 4.4 练习 1」Dis 
* Status:AC
* Tag:[lca]
* desc:询问树上任意链的长度
**/

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
    int n, m;
    readi(n, m); // 节点数，询问数
    clr(head, -1);
    repne(i, 1, n)
    {
        int u, v, w;
        readi(u, v, w); // 边的起止节点，长度
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
```

### 点分治

```c++
/**
* Number:p2634
* Title:[国家集训队]聪聪可可
* Status:AC
* Tag:[点分治]
* desc: 树上选一条链，求边权和是3的倍数的概率
**/

const int MAXN = 2e4 + 10;

struct Edge
{
    int from, to, w, nxt;
} edges[MAXN * 2];
int head[MAXN], edgeid;
void addedge(int from, int to, int w)
{
    edges[edgeid] = (Edge){from, to, w, head[from]};
    head[from] = edgeid++;
}

int root, tot, rk[MAXN], maxrk; // root-当前的重心 tot-当前子树的总节点数
bool cg[MAXN]; // 是否是重心
void getcg(int u, int pre)
{
    rk[u] = 1;
    int tmp = -INF;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre || cg[v])
            continue;
        getcg(v, u);
        tmp = max(tmp, rk[v]);
        rk[u] += rk[v];
    }
    tmp = max(tmp, tot - rk[u]);
    if (tmp < maxrk)
        root = u, maxrk = tmp;
}
int a, b; // 是3的倍数的方案数，总方案数
int allcnt[4], cnt[4]; // 之前所有子树中、当前子树中模3为i的方案数
void dfs(int u, int sum, int pre) // 当前节点，root到u的链权值之和，父节点
{
    sum = (sum % 3 + 3) % 3;
    cnt[sum]++;
    if (sum == 0)
        a += allcnt[0] + 1;
    else
        a += allcnt[3 - sum];
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre || cg[v])
            continue;
        int w = edges[i].w;
        int t = sum + w;
        dfs(v, t, u);
    }
}
void solve(int u, int nn) // u-子树中任意点 nn-子树的总节点数
{
    maxrk = INF, tot = nn;
    getcg(u, -1);
    cg[root] = true; // 计算当前子树的重心
    clr(allcnt, 0);
    for (int i = head[root]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (cg[v])
            continue;
        clr(cnt, 0);
        dfs(v, edges[i].w, -1);
        for (int i = 0; i < 3; i++)
            allcnt[i] += cnt[i];
    }
    for (int i = head[root]; ~i; i = edges[i].nxt) // 分治root的每个子树
    {
        int v = edges[i].to;
        if (cg[v])
            continue;
        solve(v, rk[v] > rk[root] ? nn - rk[root] : rk[v]);
    }
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int main()
{
    int n;
    readi(n); // 节点数
    clr(head, -1);
    repne(i, 1, n)
    {
        int x, y, w; // 边的起点，终点，权值
        readi(x, y, w);
        addedge(x, y, w);
        addedge(y, x, w);
    }
    solve(1, n);
    b = n * n;
    a = a * 2 + n;
    int d = gcd(a, b);
    printf("%d/%d", a / d, b / d);
    return 0;
}
```

### 最大匹配/最小点覆盖 Hungary

```c++
/**
* Number:uva11419
* Title:SAM I AM
* Status:AC
* Tag:[二分图, hungary, 匈牙利算法, 最小点覆盖]
* desc: 一次可以消灭一行或一列网格中的敌人，最少几次可以消灭所有敌人
**/

const int MAXN = 2e3 + 10;
const int MAXM = 2e6 + 10;

struct Edge
{
    int from, to, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

int lef[MAXN];  // 右支节点对应左支的匹配点，0表示未匹配
bool vis[MAXN]; // 是否是匈牙利树上的节点
bool dfs(int u) // 増广 u-匈牙利树的根节点
{
    vis[u] = true;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (vis[v])
            continue;
        vis[v] = true;
        if (!lef[v] || dfs(lef[v]))
        {
            lef[u] = v, lef[v] = u;
            return true;
        }
    }
    return false;
}
// 最大匹配数
int maxmatch(int nx, int ny) // nx-左支节点数量 ny-右支节点数量
{
    int ans = 0;
    fill_n(lef, nx + ny + 1, 0);
    for (int i = 1; i <= nx; i++)
    {
        fill_n(vis, nx + ny + 1, false);
        ans += dfs(i);
    }
    return ans;
}
// 输出最小点覆盖所选节点的编号
void mincover(int nx, int ny) // nx-左支节点数量 ny-右支节点数量
{
    fill_n(vis, nx + ny + 1, false);
    for (int i = 1; i <= nx; i++)
        if (!lef[i])
            dfs(i);
    for (int i = 1; i <= nx; i++)
        if (!vis[i])
            printf(" r%d", i); // 左支
    for (int i = 1; i <= ny; i++)
        if (vis[nx + i])
            printf(" c%d", i); // 右支
}

int main()
{
    int r, c, n;
    while (readi(r, c, n) != EOF && (r | c | n)) // 行数、列数、敌人数
    {
        clr(head, -1);
        edgeid = 0;
        repne(i, 0, n)
        {
            int x, y;
            readi(x, y);
            addedge(x, r + y); // 离散建图 边表示点，行号连列号
        }
        printf("%d", maxmatch(r, c)); // 最少次数
        mincover(r, c);               // 选择的行列
        puts("");
    }
    return 0;
}
```

### Hopcroft Karp

```c++
/**
 * 
 * 二分图匹配 Hopcroft-Karp
 * 
**/

#include <algorithm>
#include <queue>

#define INF 0x3f3f3f3f
const int MAXN = 100010;
const int MAXM = 300010;

struct Edge
{
    int from, to, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

int nx, ny, m; // 左支点数, 右支点数, 边数
int dep[MAXN], d;
int match[MAXN]; // i和谁匹配
bool vis[MAXN];
bool bfs()
{
    d = INF;
    std::queue<int> Q;
    std::fill_n(dep, nx + ny + 1, 0);
    for (int i = 1; i <= nx; i++)
    {
        if (!match[i])
        {
            dep[i] = 1;
            Q.push(i);
        }
    }
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if (dep[u] > d)
            break;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].to;
            if (dep[v])
                continue;
            dep[v] = dep[u] + 1;
            if (!match[v])
                d = dep[v];
            else
            {
                dep[match[v]] = dep[v] + 1;
                Q.push(match[v]);
            }
        }
    }
    return d != INF;
}
int dfs(int u)
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (vis[v] || dep[u] + 1 != dep[v])
            continue;
        vis[v] = true;
        if (match[v] && dep[v] == d)
            continue;
        if (!match[v] || dfs(match[v]))
        {
            match[u] = v, match[v] = u;
            return 1;
        }
    }
    return 0;
}
int hopcroft_karp() // 返回最大匹配数
{
    int ans = 0;
    while (bfs())
    {
        std::fill_n(vis, nx + ny + 1, false);
        for (int i = 1; i <= nx; i++)
        {
            if (!match[i])
                ans += dfs(i);
        }
    }
    return ans;
}
```

### 最佳完美匹配 KM

```c++
/**
* Number:uva11383
* Title:Golden Tiger Claw
* Status:AC
* Tag:[二分图, km, 完美匹配]
* desc: 已知方阵M，求min{sum(r[i])+sum(c[j])} s.t. M[i][j]<=r[i]+c[j]
**/

const int MAXN = 510;

int n, adj[MAXN][MAXN];      // 方阵阶数，邻接矩阵
bool visx[MAXN], visy[MAXN]; // dfs是否访问到
int lx[MAXN], ly[MAXN];      // 左右支节点的期望权值，即所求的r[]、c[]
int lef[MAXN];               // 右支的节点在左支的匹配点
bool dfs(int u)              // 匈牙利算法中的増广
{
    visx[u] = true;
    rep(v, 1, n)
    {
        if (visy[v] || lx[u] + ly[v] != adj[u][v])
            continue;
        visy[v] = true;
        if (!lef[v] || dfs(lef[v]))
        {
            lef[v] = u;
            return true;
        }
    }
    return false;
}
void update()
{
    int delta = INF;
    rep(i, 1, n) if (visx[i])
        rep(j, 1, n) if (!visy[j])
            delta = min(delta, lx[i] + ly[j] - adj[i][j]);
    rep(i, 1, n)
    {
        if (visx[i])
            lx[i] -= delta;
        if (visy[i])
            ly[i] += delta;
    }
}
int km() // KM算法，返回最佳完美匹配权值
{
    clr(lef, 0);
    clr(ly, false);
    rep(i, 1, n) lx[i] = *max_element(adj[i] + 1, adj[i] + n + 1);
    rep(i, 1, n)
    {
        while (true)
        {
            clr(visx, false);
            clr(visy, false);
            if (dfs(i))
                break;
            update();
        }
    }
    int ans = 0;
    rep(i, 1, n) ans += lx[i] + ly[i];
    return ans;
}

int main()
{
    while (readi(n) != EOF)
    {
        rep2(i, 1, n, j, 1, n) readi(adj[i][j]); // 输入的矩阵即为邻接矩阵
        int ans = km();
        rep(i, 1, n) printf("%d ", lx[i]); // r[]
        puts("");
        rep(i, 1, n) printf("%d ", ly[i]); // c[]
        puts("");
        printf("%d\n", ans); // min(sum(r[i])+sum(c[j]))
    }
    return 0;
}
```

### 网络流 最大流 Dinic ISAP

```c++
/**
* Number:luogu3376
* Title:网络最大流
* Status:AC
* Tag:[网络流最大流]
* desc: 网络流最大流模板题
**/

const int MAXN = 10010;
const int MAXM = 200010;

struct Edge
{
    int from, to, flow, nxt; // 起点，终点，容量
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int flow)
{
    edges[edgeid] = (Edge){from, to, flow, head[from]};
    head[from] = edgeid++;
}

// Dinic算法
int dep[MAXN], cur[MAXN]; // 分层，当前弧
bool bfs(int src, int dst)
{
    memset(dep, 0, sizeof(dep));
    dep[src] = 1;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dep[e.to] || e.flow <= 0) continue;
            dep[e.to] = dep[u] + 1;
            Q.push(e.to);
        }
    }
    return dep[dst] > 0;
}
int dfs(int u, int dst, int flow)
{
    if (u == dst) return flow;
    for (int &i = cur[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (dep[e.to] != dep[u] + 1 || e.flow <= 0) continue;
        int f = dfs(e.to, dst, min(flow, e.flow));
        if (f)
        {
            e.flow -= f;
            edges[i ^ 1].flow += f;
            return f;
        }
    }
    return 0;
}
int dinic(int n, int src, int dst)
{
    int ans = 0, f;
    while (bfs(src, dst))
    {
        copy(head, head + n + 1, cur);
        while (f = dfs(src, dst, INF)) ans += f;
    }
    return ans;
}

int main()
{
    int n, m, s, t;
    readi(n, m, s, t); // 点数，边数，源点，汇点
    clr(head, -1);
    while (m--)
    {
        int a, b, f; readi(a, b, f);
        addedge(a, b, f); addedge(b, a, 0); // 双向边
    }
    printf("%d\n", dinic(n, s, t));
    // printf("%d\n", isap(n, s, t));
    return 0;
}
```

```c++
// ISAP算法
int dep[MAXN], cur[MAXN], num[MAXN], pre[MAXN];
void bfs(int n, int dst)
{
    queue<int> Q;
    fill_n(dep, n + 1, n);
    dep[dst] = 0;
    Q.push(dst);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i ^ 1];
            if (dep[e.from] < n || e.flow <= 0) continue;
            dep[e.from] = dep[u] + 1;
            Q.push(e.from);
        }
    }
}
ll augment(int src, int dst)
{
    ll f = INF;
    for (int u = dst; u != src; u = edges[pre[u]].from)
        f = min(f, edges[pre[u]].flow);
    for (int u = dst; u != src; u = edges[pre[u]].from)
    {
        edges[pre[u]].flow -= f;
        edges[pre[u] ^ 1].flow += f;
    }
    return f;
}
ll isap(int n, int src, int dst)
{
    fill_n(num, n + 1, 0);
    bfs(n, dst);
    for (int i = 1; i <= n; i++)
    {
        num[dep[i]]++;
        cur[i] = head[i];
    }
    int u = src;
    ll ans = 0;
    while (dep[src] < n)
    {
        if (u == dst)
        {
            ans += augment(src, dst);
            u = src;
            continue;
        }
        bool found = false;
        for (int &i = cur[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dep[e.to] + 1 != dep[u] || e.flow <= 0) continue;
            found = true;
            u = e.to;
            pre[u] = i;
            break;
        }
        if (!found)
        {
            int mindep = n - 1;
            for (int i = head[u]; ~i; i = edges[i].nxt)
            {
                Edge &e = edges[i];
                if (e.flow > 0) mindep = min(mindep, dep[e.to]);
            }
            if (--num[dep[u]] == 0) break;
            num[dep[u] = mindep + 1]++;
            cur[u] = head[u];
            if (u != src) u = edges[pre[u]].from;
        }
    }
    return ans;
}
```

### 最小费用最大流

```c++
/**
* Number:luogu3381
* Title:最小费用最大流
* Status:AC
* Tag:[最小费用最大流]
* desc: 最小费用最大流模板题
**/

const int MAXN = 5010;
const int MAXM = 100010;

struct Edge
{
    int from, to, flow, dis, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, int flow, int dis)
{
    edges[edgeid] = (Edge){from, to, flow, dis, head[from]};
    head[from] = edgeid++;
}

int dis[MAXN], pre[MAXN]; // 最短路长度，最短路树
bool vis[MAXN];
bool spfa(int n, int src, int dst)
{
    fill_n(dis, n + 1, INF);
    dis[src] = 0;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (e.flow <= 0 || dis[u] + e.dis >= dis[e.to]) continue;
            dis[e.to] = dis[u] + e.dis;
            pre[e.to] = i;
            if (!vis[e.to])
            {
                Q.push(e.to);
                vis[e.to] = true;
            }
        }
    }
    return dis[dst] < INF;
}
int maxflow, mincost; // 最大流，取得最大流的最小费用
void mcmf(int n, int src, int dst)
{
    maxflow = mincost = 0;
    while (spfa(n, src, dst))
    {
        int f = INF;
        for (int u = dst; u != src; u = edges[pre[u]].from)
            f = min(f, edges[pre[u]].flow);
        for (int u = dst; u != src; u = edges[pre[u]].from)
        {
            edges[pre[u]].flow -= f;
            edges[pre[u] ^ 1].flow += f;
            mincost += f * edges[pre[u]].dis;
        }
        maxflow += f;
    }
}

int main()
{
    int n, m, s, t;
    readi(n, m, s, t); // 点数，边数，源点，汇点
    clr(head, -1);
    while (m--)
    {
        int u, v, w, f;
        readi(u, v, w, f); // 起点，终点，容量，费用
        addedge(u, v, w, f); addedge(v, u, 0, -f); // 双向边
    }
    mcmf(n, s, t);
    printf("%d %d", maxflow, mincost);
    return 0;
}
```

### 单连通分量 2-SAT Tarjan

```c++
/**
* Number:loj10097
* Title:「一本通 3.5 练习 5」和平委员会
* Status:AC
* Tag:[2-sat, tarjan]
* desc: n个党派，2n个代表，2i-1和2i属于一个党派，m对代表不能共存，输出每个党派选一名代表的方案
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

const int MAXN = 8010 * 4;
const int MAXM = 2e6 + 10;
struct Edge
{
    int from, to, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}
void addedge2(int u, int v)
{
    addedge(u, v);
    addedge(v, u);
}

int dfn[MAXN], low[MAXN], dfsid; // dfs序，dfs树上可以连接的最小节点
int grp[MAXN], grpid;            // 节点的分组号，是逆拓扑序
stack<int> trace;                // 当前dfs路径
void tarjan(int u)
{
    dfn[u] = low[u] = ++dfsid;
    trace.push(u);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (!dfn[v])
            tarjan(v); // 如果v没有计算过，先tarjan点v
        if (!grp[v])
            low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u]) // u是强联通分量的根节点
    {
        grp[u] = ++grpid;
        while (trace.top() != u)
        {
            grp[trace.top()] = grpid;
            trace.pop();
        }
        trace.pop();
    }
}

int main()
{
    int n, m;
    readi(n, m); // 点数，边数
    clr(head, -1);
    repne(i, 0, m)
    {
        int u, v;
        readi(u, v); // u与v有矛盾
        u--, v--;
        // u-选u u^1-选u的对立面
        // u->v表示如果选u则一定要选v
        addedge(u, v ^ 1);
        addedge(v, u ^ 1);
    }
    rep(i, 1, n << 1) if (!dfn[i]) tarjan(i);
    rep(i, 1, n << 1)
    {
        if (grp[i] == grp[i ^ 1]) // 矛盾
        {
            printf("NIE");
            return 0;
        }
    }
    rep(i, 1, n << 1) if (grp[i] < grp[i ^ 1])
        // (i^1)->(i)，选了(i^1)就必须选(i)，那么只能选i
        printf("%d\n", i);
    return 0;
}
```

### 字符串哈希

```c++
struct string_hash
{
    ull _hashc[2000010], *hashc;
    const ull base = 233; // 大于字符种类数的质数
    ull powb[2000010] = {1};
    void init(char *s) // 初始化，计算powb、hashc
    {
        hashc = _hashc + 1;
        for (int i = 0; s[i]; i++)
        {
            powb[i + 1] = powb[i] * base;
            hashc[i] = hashc[i - 1] * base + s[i];
        }
    }
    ull substr(int lt, int rt) // 子串s[lt : rt]的哈希值
    {
        return hashc[rt] - hashc[lt - 1] * powb[rt - lt + 1];
    }
    ull concat(int lt1, int rt1, int lt2, int rt2) //s[lt1 : rt1] + s[lt2 : rt2]的哈希值
    {
        if (lt1 > rt1 && lt2 > rt2)
            return 0ULL;
        if (lt1 > rt1)
            return substr(lt2, rt2);
        if (lt2 > rt2)
            return substr(lt1, rt1);
        return substr(lt1, rt1) * powb[rt2 - lt2 + 1] + substr(lt2, rt2);
    }
};
```

### KMP

```c++
struct kmp
{
    int nxt[1000010];
    void init_nxt(const char* pat) // 初始化，计算nxt数组
    {
        int pre = -1, cur = 0;
        nxt[0] = -1;
        while(pat[cur])
        {
            if(pre == -1 || pat[pre] == pat[cur])
            {
                pre++, cur++;
                // next数组优化，表示最终回退位置
                nxt[cur] = (pat[pre] == pat[cur] ? nxt[pre] : pre);
                //不优化，表示最大前后缀长度
                // nxt[cur] = pre;
            }
            else
            {
                pre = nxt[pre];
            }
        }
    }
    void operator()(const char* dst, const char* pat) // 匹配
    {
        int i = 0, j = 0;
        while(dst[i])
        {
            if(j == -1 || dst[i] == pat[j])
            {
                i++, j++;
                if(pat[j] == '\0')
                {
                    // 匹配dst[i-j:i-1]
                    j=nxt[j];
                }
            }
            else j = nxt[j];
        }
    }
};
```

### 扩展KMP

```c++
struct extend_kmp
{
    int nxt[100010] /* 最长前缀 */, ext[100010];
    void init_nxt(const char* pat) // 初始化，计算nxt数组
    {
        int p = 0, mx = 0, i;
        for(i = 1; pat[i]; i++)
        {
            int k = i > mx ? i : i + nxt[i - p] - 1;
            if(k < mx)nxt[i] = nxt[i - p];
            else
            {
                k = mx + 1;
                int j = i > mx ? 0 : k - i;
                while(pat[k] && pat[k] == pat[j])k++, j++;
                p = i;
                mx = std::max(p, k - 1);
                nxt[i] = k - i;
            }
        }
        nxt[0] = i;
    }
    void operator()(const char* dst, const char* pat) // 匹配，计算ext数组
    {
        int p, mx = -1, i;
        for(i = 0; dst[i]; i++)
        {
            int k = i > mx ? i : i + nxt[i - p] - 1;
            if(k < mx)ext[i] = nxt[i - p];
            else
            {
                int k = mx + 1;
                int j = k - i;
                while(dst[k] && dst[k] == pat[j])k++, j++;
                p = i;
                mx = std::max(p, k - 1);
                ext[i] = k - i;
            }
        }
    }
};
```

### Manacher

```c++
struct manacher
{
    char s[2000100]; // #分隔的字符串
    int palin[2000100]; // 以i为对称轴的回文串长度为palin[i]-1
    void loadString(const char* str)
    {
        char* p = s;
        *(p++) = '#';
        const char* q = str;
        while(*q)
        {
            *(p++) = *(q++);
            *(p++) = '#';
        }
    }
    void calc_palin() // 计算palin数组
    {
        int p, far = 0;
        for(int i = 0; s[i]; i++)
        {
            int lt, rt;
            if(i < far)rt = std::min(i + palin[(p << 1) - i] - 1, far);
            else rt = i;
            lt = (i << 1) - rt;
            while(lt >= 0 && s[lt] == s[rt])lt--, rt++;
            if(rt - 1 > far)
            {
                far = rt - 1;
                p = i;
            }
            palin[i] = rt - i;
        }
    }
};
```

### 字典树 Trie

```c++
struct Trie
{
    struct Node
    {
        int count; // 当前节点是多少个单词的结尾
        Node* nxt[26];
    }nodes[100010];
    int sz; // 节点总数
    Node* root; // 根节点
    Node* createNode()
    {
        Node* nod = &nodes[sz++];
        memset(nod, 0, sizeof(Node));
        return nod;
    }
    void init() // 初始化，清空字典树
    {
        sz = 0;
        root = createNode();
    }
    inline int id(char ch) // 字符映射到边
    {
        return ch - 'a';
    }
    int insert(const char* s) // 插入单词
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = id(*p);
            if(!nod->nxt[v])
            {
                nod->nxt[v] = createNode();
            }
            nod = nod->nxt[v];
            p++;
        }
        return nod->count++;
    }
    int find(const char* s) // 查找单词，返回出现次数
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = id(*p);
            if(!nod->nxt[v])return 0;
            nod = nod->nxt[v];
            p++;
        }
        return nod->count;
    }
};
```

### 后缀自动机 SAM

```c++
/**
* Number:spoj1812
* Title:Longest Common Substring II
* Status:AC
* Tag:[后缀自动机, sam]
* desc: 求多个字符串的最长公共子串长度
**/

const int MAXN = 1e5 + 10;

struct Node
{
    int link, len, nxt[26]; // 后缀链接，当前节点可以表示的最长子串长度
} sam[MAXN << 1];
int sz = 1, last = 1; // 后缀自动机节点个数，最新的节点编号
void extend(int ch)
{
    int cur = ++sz, pre = last;
    sam[cur].len = sam[pre].len + 1;
    while (pre && !sam[pre].nxt[ch])
    {
        sam[pre].nxt[ch] = cur;
        pre = sam[pre].link;
    }
    if (!pre)
        sam[cur].link = 1;
    else
    {
        int ori = sam[pre].nxt[ch];
        if (sam[ori].len == sam[pre].len + 1)
            sam[cur].link = ori;
        else
        {
            int clone = ++sz;
            sam[clone] = sam[ori];
            sam[clone].len = sam[pre].len + 1;
            sam[cur].link = sam[ori].link = clone;
            while (pre && sam[pre].nxt[ch] == ori)
            {
                sam[pre].nxt[ch] = clone;
                pre = sam[pre].link;
            }
        }
    }
    last = cur;
}

char s[MAXN];
int bin[MAXN], ord[MAXN << 1];       // 桶，节点的拓扑序
int dp[MAXN << 1], dpall[MAXN << 1]; // 当前串与第一个串在节点i匹配的最大长度
int main()
{
    reads(s);
    int L = strlen(s);
    for (char *p = s; *p; p++)
        extend(*p - 'a');            // 建第一个字符串的后缀自动机
    rep(i, 2, sz) bin[sam[i].len]++; // 桶排序，节点按len排序就是拓扑序
    rep(i, 1, L) bin[i] += bin[i - 1];
    rep(i, 2, sz) ord[bin[sam[i].len]--] = i; // 排序后第i个节点编号是ord[i]
    clr(dpall, INF);
    while (reads(s) != EOF)
    {
        clr(dp, 0);
        int cur = 1, len = 0;
        for (char *p = s; *p; p++)
        {
            int ch = *p - 'a';
            if (sam[cur].nxt[ch]) // 匹配，长度+1
            {
                cur = sam[cur].nxt[ch];
                len++;
                dp[cur] = max(dp[cur], len);
                continue;
            }
            while (cur && !sam[cur].nxt[ch])
                cur = sam[cur].link; // 失配，沿后缀链接后退
            if (cur == 0)
                cur = 1, len = 0; // 如果退到空串
            else
            {
                len = sam[cur].len + 1;
                cur = sam[cur].nxt[ch];
                dp[cur] = max(dp[cur], len);
            }
        }
        for (int i = sz - 1; i >= 1; i--) // dp沿后缀链接向上传递
        {
            int u = ord[i];
            // 如果字符串u可以匹配，它的后缀一定可以匹配
            if (dp[u]) dp[sam[u].link] = sam[sam[u].link].len;
        }
        rep(i, 2, sz) dpall[i] = min(dpall[i], dp[i]);
    }
    int ans = *max_element(dpall + 2, dpall + sz + 1);
    printf("%d", ans);
    return 0;
}
```

### 高斯消元

```c++
const int MAXN = 104;
const double eps = 1e-15;
struct gauss_elimination
{
    double* mat[MAXN];
    // 保证系数矩阵为方阵，化为行最简矩阵
    int operator()(double arr[][MAXN], int nequ) // 系数矩阵，行数
    {
        for(int i = 0; i < nequ; i++)
            mat[i] = arr[i];
        int nvar = 0;
        for(int c = 0; c < nequ; c++)
        {
            int k = -1;
            double tmp = 0;
            for(int r = nvar; r < nequ; r++)
                if(fabs(mat[r][c]) > tmp)
                    tmp = fabs(mat[r][c]), k = r;
            if(k == -1)continue;
            std::swap(mat[nvar], mat[k]);
            for(int r = 0; r < nequ; r++)
            {
                if(fabs(mat[r][c]) < eps || r == nvar)continue;
                for(int i = c + 1; i <= nequ; i++)
                {
                    mat[r][i] -= mat[nvar][i] / mat[nvar][c] * mat[r][c];
                }
                mat[r][c] = 0;
            }
            nvar++;
        }
        for(int r = 0; r < nvar; r++)
        {
            bool zero = true;
            for(int c = r; c < nequ; c++)
            {
                if(fabs(mat[r][c]) > eps)
                {
                    zero = false;
                    break;
                }
            }
            if(zero && fabs(mat[r][nequ]) > eps)return 0; // 无解
        }
        return nvar; // 返回主元个数
    }
};
```

### 计算几何

```c++
const double eps = 1e-8; // 精度
const double PI = acos(-1); // 圆周率

// 控制精度的比较函数
// x==0返回0, x>0返回1, x<0返回-1
inline int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    return x > 0 ? 1 : -1;
}

inline double radToDeg(double ang)
{
    return ang / PI * 180.;
}

inline double degToRad(double ang)
{
    return ang / 180. * PI;
}

/************************************************************
 * 
 * 点, 向量
 * 
************************************************************/

struct Vector
{
    double x, y;
    Vector(){}
    Vector(double _x, double _y) : x(_x), y(_y){}
};
typedef Vector Point;

bool operator==(const Point& lhs, const Point& rhs)
{
    return sgn(lhs.x - rhs.x) == 0 && sgn(lhs.y - rhs.y) == 0;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Point& lhs, const Point& rhs)
{
    return sgn(lhs.x - rhs.x) < 0 || sgn(lhs.x - rhs.x) == 0 && sgn(lhs.y - rhs.y) < 0;
}

inline Vector operator+(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector operator-(const Vector& v)
{
    return Vector(-v.x, -v.y);
}

inline Vector operator-(const Vector& lhs, const Vector& rhs)
{
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector operator*(const Vector& lhs, double rhs)
{
    return Vector(lhs.x * rhs, lhs.y * rhs);
}

inline Vector operator*(double lhs, const Vector& rhs)
{
    return rhs * lhs;
}

inline Vector operator/(const Vector& lhs, double rhs)
{
    return Vector(lhs.x / rhs, lhs.y / rhs);
}

// 向量的模长
inline double len(const Vector& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

// 两点间的距离
inline double dist(const Point& lhs, const Point& rhs)
{
    return len(lhs - rhs);
}

// 向量的点积
inline double dot(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

// 向量的叉积
inline double cross(const Vector& lhs, const Vector& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

// 向量的倾斜角，弧度制
inline double angle(const Vector& v)
{
    return atan2(v.y, v.x);
}

// 向量的夹角，弧度制
inline double angle(const Vector& lhs, const Vector& rhs)
{
    return acos(dot(lhs, rhs) / len(lhs) / len(rhs));
}

// 单位向量
inline Vector normalized(const Vector& lhs)
{
    double L = len(lhs);
    return Vector(lhs.x / L, lhs.y / L);
}

// 单位法向量，在lhs左侧
inline Vector normal(const Vector& lhs)
{
    return normalized(Vector(-lhs.y, lhs.x));
}

// 将向量v顺时针旋转theta弧度
inline Vector rotate(const Vector& v, double theta)
{
    double s = sin(theta), c = cos(theta);
    return Vector(v.x * c - v.y * s, v.x * s + v.y * c);
}


/************************************************************
 * 
 * 直线, 线段
 * 
************************************************************/

struct Line
{
    Point p1, p2;
};

struct Segment
{
    Point p1, p2;
};

// 直线line的倾斜角
double angle(const Line& line)
{
    Vector v = line.p2 - line.p1;
    return atan2(v.y, v.x);
}

// 直线line的单位法向量
Vector normal(const Line& line)
{
    Vector v = normal(line.p2 - line.p1);
    return normalized(v);
}

// 将line沿法向量方向平移d
Line shift(const Line& line, double d)
{
    Vector dir = normal(line);
    return (Line){line.p1 + dir * d, line.p2 + dir* d};
}

// 点到直线的距离
double dist(const Point& p, const Line& line)
{
    Vector v1 = line.p1 - line.p2, v2 = p - line.p1;
    return fabs(cross(v1, v2)) / len(v1);
}

// 点到线段的距离
double dist(const Point& p, const Segment& seg)
{
    if(seg.p1 == seg.p2)return len(p - seg.p1);
    Vector dir = seg.p2 - seg.p1;
    Vector v1 = p - seg.p1, v2 = p - seg.p2;
    if(sgn(dot(dir, v1)) < 0)return len(v1);
    if(sgn(dot(dir, v2)) > 0)return len(v2);
    return fabs(cross(dir, v1)) / len(dir);
}

// 直线line的一般方程ax+by+c=0
void equation(const Line& line, double& a, double& b, double& c)
{
    a = line.p2.y - line.p1.y;
    b = line.p1.x - line.p2.x;
    c = -a * line.p1.x - b * line.p1.y;
}

// 点p在直线line上的投影
Point project(const Point& p, const Line& line)
{
    Vector v = line.p2 - line.p1;
    return line.p1 + v * (dot(v, p - line.p1) / dot(v,v));
}

// 点与直线的位置关系
// 点在直线外 0
// 点在直线上 1
int position(const Point& p, const Line& line)
{
    return sgn(cross(p - line.p1, p - line.p2)) == 0;
}

// 点与线段的位置关系
// 点在线段外 -1
// 点在线段的延长线上 0
// 点在线段端点上 1
// 点在线段内部 2
int position(const Point& p, const Segment& seg)
{
    if(position(p, *(Line*)&seg) == 0)return -1;
    int d = sgn(dot(p - seg.p1, p - seg.p2));
    if(d > 0)return 0;
    if(d == 0)return 1;
    return 2;
}

// 直线与直线的位置关系
// 相交 -1, 
// 重合 0, 
// 平行 1
int position(const Line& lhs, const Line& rhs)
{
    if(sgn(cross(lhs.p2 - lhs.p1, rhs.p2 - rhs.p1)) == 0)
    {
        if(sgn(cross(lhs.p2 - lhs.p1, rhs.p1 - lhs.p1)) == 0)return 0;
        else return 1;
    }
    return -1;
}

// 直线与线段的位置关系
// 线段跨过直线 -1, 
// 线段至少一个端点在直线上 0, 
// 相离 1
int position(const Line& line, const Segment& seg)
{
    Vector dir = line.p2 - line.p1;
    Vector v1 = seg.p1 - line.p1, v2 = seg.p2 - line.p1;
    return sgn(cross(dir, v1)) * sgn(cross(dir, v2));
}

// 两线段的位置关系
// 规范相交 -1, 
// 非规范相交 0, 
// 相离 1
int position(const Segment& lhs, const Segment& rhs)
{
    int d1 = sgn(cross(lhs.p2 - lhs.p1, rhs.p1 - lhs.p1));
    int d2 = sgn(cross(lhs.p2 - lhs.p1, rhs.p2 - lhs.p1));
    int d3 = sgn(cross(rhs.p2 - rhs.p1, lhs.p1 - rhs.p1));
    int d4 = sgn(cross(rhs.p2 - rhs.p1, lhs.p2 - rhs.p1));
    if((d1 ^ d2) == -2 && (d3 ^ d4) == -2)return -1;
    return !((d1 == 0 && sgn(dot(rhs.p1 - lhs.p1, rhs.p1 - lhs.p2)) <= 0) 
        || (d2 == 0 && sgn(dot(rhs.p2 - lhs.p1, rhs.p2 - lhs.p2)) <= 0) 
        || (d3 == 0 && sgn(dot(lhs.p1 - rhs.p1, lhs.p1 - rhs.p2)) <= 0) 
        || (d4 == 0 && sgn(dot(lhs.p2 - rhs.p1, lhs.p2 - rhs.p2)) <= 0)); 
}

// 两直线的交点，需要保证两直线相交
Point intersect(const Line& lhs, const Line& rhs)
{
    double a1 = lhs.p2.y - lhs.p1.y;
    double b1 = lhs.p1.x - lhs.p2.x;
    double c1 = cross(lhs.p2, lhs.p1);
    double a2 = rhs.p2.y - rhs.p1.y;
    double b2 = rhs.p1.x - rhs.p2.x;
    double c2 = cross(rhs.p2, rhs.p1);
    double d = a1 * b2 - a2 * b1;
    return Point((b1 * c2 - b2 * c1) / d, (c1 * a2 - c2 * a1) / d);
}


/************************************************************
 * 
 * 多边形, 凸包
 * 
************************************************************/

typedef std::vector<Point> Polygen;

// 多边形的周长
double circumference(const Polygen& poly)
{
    int n = poly.size();
    double ans = 0;
    for(int i = 0; i < n; i++)
    {
        ans += len(poly[i] - poly[(i + 1) % n]);
    }
    return ans;
}

// 多边形面积
double area(const Polygen& p)
{
	double ans = 0;
	for(int i = 1; i < (int)p.size() - 1; i++)
		ans += cross(p[i] - p[0], p[i + 1] - p[0]);
	return ans / 2.0;
}

// 点与多边形的位置关系
// 点在多边形外部 -1,
// 在边上 0,
// 在内部 1
int position(const Point& p, const Polygen& poly)
{
    int k = 0, n = poly.size();
    for(int i = 0; i < n; i++)
    {
        const Point &p1 = poly[i], &p2 = poly[(i + 1) % n];
        if(position(p, (Segment){p1, p2}) == 1)return 0;
        int d = sgn(cross(p - p1, p2 - p1));
        int s1 = sgn(p1.y - p.y);
        int s2 = sgn(p2.y - p.y);
        if(d > 0 && s1 < 0 && s2 >= 0)k++;
        else if(d < 0 && s2 < 0 && s1 >= 0)k--;
    }
    return k ? 1 : -1;
}

// 凸包
Polygen ConvexHull(std::vector<Point>& points)
{
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if(points.size() <= 2)return points;
    int n = points.size();
    Polygen ans({points[0], points[1]});
    int sz;
    for(int i = 2; i < n; i++) {
        while((sz = ans.size()) >= 2 && 
            sgn(cross(ans[sz - 1] - ans[sz - 2], points[i] - ans[sz - 2])) <= 0)
            ans.pop_back();
        ans.push_back(points[i]);
    }
    int sz0 = ans.size();
    for(int i = n - 2; i >= 0; i--) {
        while((sz = ans.size()) > sz0 && 
            cross(ans[sz - 1] - ans[sz - 2], points[i] - ans[sz - 2]) <= 0)
            ans.pop_back();
        ans.push_back(points[i]);
    }
    if(n > 1)ans.pop_back();
    return ans;
}

// 旋转卡壳，求凸包直径
double rotatingCalipers(const Polygen& poly)
{
    int n = poly.size(), p = 1;
    double ans = 0;
    for(int i = 0; i < n; i++)
    {
        Vector b = poly[(i + 1) % n] - poly[i];
        while(cross(b, poly[(p + 1) % n] - poly[i])
            > cross(b, poly[p] - poly[i]))
            p = (p + 1) % n;
        ans = std::max(ans, std::max(len(poly[p] - poly[i]), 
            len(poly[(p + 1) % n] - poly[i])));
    }
    return ans;
}

// 多边形与多边形的位置关系,
// lhs内含于rhs -2,
// lhs与rhs相交 -1,
// lhs包含rhs 0
// 相离 1
int position(const Polygen& lhs, const Polygen& rhs)
{
    int n = lhs.size(), m = rhs.size();
    for(int i = 0; i < n; i++)
    {
        if(position(lhs[i], rhs) >= 0)return -2;
    }
    for(int i = 0; i < m; i++)
    {
        if(position(rhs[i], lhs) >= 0)return 0;
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(position((Segment){lhs[i], lhs[(i + 1) % n]}, 
                (Segment){rhs[j], rhs[(j + 1) % m]}) <= 0)
            {
                return -1;
            }
        }
    }
    return 1;
}


/************************************************************
 * 
 * 圆
 * 
************************************************************/

struct Circle
{
    Point c; // 圆心
    double r; // 半径
};

// 获取circle在圆心角ang处的点
Point getPoint(const Circle& circle, double ang)
{
    return Point(circle.c.x + circle.r * cos(ang), 
        circle.c.y + circle.r * sin(ang));
}

// 从from到to的弧长
double arc(const Circle& circle, const Point& from, const Point& to)
{
    Vector v1 = from - circle.c, v2 = to - circle.c;
    double ang1 = angle(v1), ang2 = angle(v2);
    if(ang2 < ang1)ang2 += 2 * PI;
    return circle.r * (ang2 - ang1);
}

// 直线与圆交点, 输出参数ans[]，返回交点个数
int intersect(const Line& L, const Circle& C, Point ans[])
{
    Vector v = L.p2 - L.p1;
    double a = v.x, b = L.p1.x - C.c.x, c = v.y, d = L.p1.y - C.c.y;
    double e = a * a + c * c;
    double f = 2 * (a * b + c * d);
    double g = b * b + d * d - C.r * C.r;
    double delta = f * f - 4. * e * g;
    int s = sgn(delta);
    if(s < 0) return 0; // 相离
    else if(s == 0) // 相切
    {
        ans[0] = L.p1 + (-f / (2. * e)) * v;
        return 1;
    }
    else // 相交
    {
        ans[0] = L.p1 + ((-f - sqrt(delta)) / (2. * e)) * v;
        ans[1] = L.p1 + ((-f + sqrt(delta)) / (2. * e)) * v;
        return 2;
    }
}

// 圆与圆交点，返回交点个数，
// -1表示无穷多个交点
int intersect(const Circle& C1, const Circle& C2, Point ans[])
{
    double d = len(C1.c - C2.c);
    if(sgn(d) == 0)
    {
        if(sgn(C1.r - C2.r) == 0)return -1; //重合
        return 0;
    }
    if(sgn(C1.r + C2.r - d) < 0)return 0;
    if(sgn(fabs(C1.r - C2.r) - d) > 0)return 0;
    double a = angle(C2.c - C1.c);
    double da = acos((C1.r * C1.r + d * d-C2.r * C2.r) / (2 * C1.r * d));
    Point p1 = getPoint(C1, a - da),p2 = getPoint(C1, a + da);
    ans[0] = p1;
    if(p1 == p2)return 1;
    ans[1] = p2;
    return 2;
}

// P到圆C的切线，ans[]储存切线的方向向量
int tangent(const Circle& C, const Point& p, Point ans[])
{
    Point u = C.c - p;
    double dist = len(u);
    if(dist < C.r)return 0;
    else if(sgn(dist - C.r) == 0)
    {
        ///p在圆上仅有一条切线
        ans[0] = rotate(u, PI / 2);
        return 1;
    }
    else
    {
        double ang = asin(C.r / dist);
        ans[0] = rotate(u, -ang);
        ans[1] = rotate(u, ang);
        return 2;
    }
}

// 两圆公切线，a[] b[]分别为公切线在圆A B上的切点，返回公切线条数
int tangent(Circle A, Circle B, Point* a, Point* b)
{
    int cnt = 0;
    if(A.r < B.r) { std::swap(A, B); std::swap(a, b); }
    int d2 = (A.c.x - B.c.x) * (A.c.x - B.c.x)+(A.c.y - B.c.y) * (A.c.y - B.c.y);
    int rdiff = A.r - B.r;
    int rsum = A.r+B.r;
    if(d2 < rdiff * rdiff)return 0; // 内含
    double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
    if(d2 == 0 && A.r == B.r)return -1; ///无穷多
    if(d2 == rdiff * rdiff) // 内切 1条
    {
        a[cnt] = getPoint(A, base); b[cnt] = getPoint(B, base); cnt++;
        return 1;
    }
    // 外切
    double ang = acos((A.r - B.r) / sqrt(d2));
    a[cnt] = getPoint(A, base + ang); b[cnt] = getPoint(B, base + ang); cnt++;
    a[cnt] = getPoint(A, base - ang); b[cnt] = getPoint(B, base - ang); cnt++;
    if(d2 == rsum * rsum) // one
    {
        a[cnt] = getPoint(A, base); b[cnt] = getPoint(B, PI+base); cnt++;
    }
    else if(d2>rsum * rsum) // two
    {
        double ang = acos((A.r - B.r) / sqrt(d2));
        a[cnt] = getPoint(A, base + ang); b[cnt] = getPoint(B, PI + base+ang); cnt++;
        a[cnt] = getPoint(A, base - ang); b[cnt] = getPoint(B, PI+base - ang); cnt++;
    }
    return cnt;
}

// 三角形外接圆
Circle CircumscribedCircle(const Point& p1, const Point& p2, const Point& p3)
{
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx * Cy - By * Cx);
    double cx = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy))/D + p1.x;
    double cy = (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By))/D + p1.y;
    Point p = Point(cx, cy);
    return (Circle){p, len(p1 - p)};
}

// 三角形内切圆
Circle InscribedCircle(const Point& p1, const Point& p2, const Point& p3)
{
    double a = len(p2 - p3);
    double b = len(p3 - p1);
    double c = len(p1 - p2);
    Point p = (p1 * a + p2 * b + p3 * c)/(a + b + c);
    return (Circle){p, dist(p, (Line){p1, p2})};
}
```



### regex

```c++
#include <iostream>
#include <string>
#include <regex>
int main()
{
    // Simple regular expression matching
    const std::string fnames[] = {"foo.txt", "bar.txt", "baz.dat", "zoidberg"};
    const std::regex txt_regex("[a-z]+\\.txt");
 
    for (const auto &fname : fnames) {
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';
    }   
 
    // Extraction of a sub-match
    const std::regex base_regex("([a-z]+)\\.txt");
    std::smatch base_match;
 
    for (const auto &fname : fnames) {
        if (std::regex_match(fname, base_match, base_regex)) {
            // The first sub_match is the whole string; the next
            // sub_match is the first parenthesized expression.
            if (base_match.size() == 2) {
                std::ssub_match base_sub_match = base_match[1];
                std::string base = base_sub_match.str();
                std::cout << fname << " has a base of " << base << '\n';
            }
        }
    }
    // Extraction of several sub-matches
    const std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
    std::smatch pieces_match;
 
    for (const auto &fname : fnames) {
        if (std::regex_match(fname, pieces_match, pieces_regex)) {
            std::cout << fname << '\n';
            for (size_t i = 0; i < pieces_match.size(); ++i) {
                std::ssub_match sub_match = pieces_match[i];
                std::string piece = sub_match.str();
                std::cout << "  submatch " << i << ": " << piece << '\n';
            }   
        }   
    }   
}
```

```c++
int main()
{
    std::string lines[] = {"Roses are #ff0000",
                           "violets are #0000ff",
                           "all of my base are belong to you"};
    std::regex color_regex("#([a-f0-9]{2})"
                            "([a-f0-9]{2})"
                            "([a-f0-9]{2})");
    // simple match
    for (const auto &line : lines) {
        std::cout << line << ": " << std::boolalpha
                  << std::regex_search(line, color_regex) << '\n';
    }   
    std::cout << '\n';
    // show contents of marked subexpressions within each match
    std::smatch color_match;
    for (const auto& line : lines) {
        if(std::regex_search(line, color_match, color_regex)) {
            std::cout << "matches for '" << line << "'\n";
            std::cout << "Prefix: '" << color_match.prefix() << "'\n";
            for (size_t i = 0; i < color_match.size(); ++i) 
                std::cout << i << ": " << color_match[i] << '\n';
            std::cout << "Suffix: '" << color_match.suffix() << "\'\n\n";
        }
    }
    // repeated search (see also std::regex_iterator)
    std::string log(R"(
        Speed:	366
        Mass:	35
        Speed:	378
        Mass:	32
        Speed:	400
	Mass:	30)");
    std::regex r(R"(Speed:\t\d*)");
    std::smatch sm;
    while(regex_search(log, sm, r))
    {
        std::cout << sm.str() << '\n';
        log = sm.suffix();
    }
    // C-style string demo
    std::cmatch cm;
    if(std::regex_search("this is a test", cm, std::regex("test"))) 
        std::cout << "\nFound " << cm[0] << " at position " << cm.prefix().length();
}
```

```c++
#include <iterator>
#include <regex>
int main()
{
   std::string text = "Quick brown fox";
   std::regex vowel_re("a|e|i|o|u");
   // write the results to an output iterator
   std::regex_replace(std::ostreambuf_iterator<char>(std::cout),
                      text.begin(), text.end(), vowel_re, "*");
   // construct a string holding the results
   std::cout << '\n' << std::regex_replace(text, vowel_re, "[$&]") << '\n';
}
```

