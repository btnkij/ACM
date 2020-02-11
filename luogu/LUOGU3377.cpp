/**
* Number:luogu3377
* Title:【模板】左偏树（可并堆）
* Status:AC
* Tag:[左偏树, 可并堆]
* desc: 维护n个小根堆，支持合并堆、删除最小值的操作
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 1e5 + 10;
struct Node // 左偏树节点
{
    int dis, son[2]; // 左偏树节点必要信息：dis-到最近空节点的距离 son[]-左右儿子
    int val, pos;    // val-值 pos-位置
    bool operator<(const Node &rhs) const
    {
        return val < rhs.val || val == rhs.val && pos < rhs.pos;
    }
} tree[MAXN];
int join(int x, int y) // 合并x,y所在的堆，保证x,y都是堆顶，返回新的根
{
    if (!x || !y)
        return x | y;      // 若x,y其中一个为空节点，返回另外一个节点
    if (tree[y] < tree[x]) // 保证小根堆的性质
        swap(x, y);
    int &lc = tree[x].son[0], &rc = tree[x].son[1];
    rc = join(rc, y);
    if (tree[lc].dis < tree[rc].dis) // 保证左偏性：左链长于右链
        swap(lc, rc);
    tree[x].dis = tree[rc].dis + 1;
    return x;
}

int fa[MAXN];
int findr(int x) // 并查集模板
{
    return x == fa[x] ? x : fa[x] = findr(fa[x]);
}

bool del[MAXN]; // 标记节点是否被删除
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m);             // n-小根堆个数 m-操作数
    tree[0].dis = -1;        // 左偏树初始化：空节点的dis=-1
    iota(fa, fa + n + 1, 0); // 并查集的初始化
    rep(i, 1, n)
    {
        readi(tree[i].val); // 初始每个节点单独成堆
        tree[i].pos = i;
    }
    while (m--)
    {
        int op;
        readi(op);
        if (op == 1) // 合并x,y所在的堆
        {
            int x, y;
            readi(x, y);
            if (del[x] || del[y] || findr(x) == findr(y))
                continue;               // 无效操作
            x = findr(x), y = findr(y); // 找到堆顶
            fa[x] = fa[y] = join(x, y); // 注意维护并查集
        }
        else if (op == 2) // 弹出x所在堆的最小值
        {
            int x;
            readi(x);
            if (del[x])
            {
                puts("-1"); // 无效操作
                continue;
            }
            x = findr(x);                // 找到堆顶
            printf("%d\n", tree[x].val); // 输出最小值
            int lc = tree[x].son[0], rc = tree[x].son[1];
            fa[x] = fa[lc] = fa[rc] = join(lc, rc); // 合并左右儿子，即弹出堆顶
            del[x] = true;                          // 删除标记
        }
    }
    return 0;
}