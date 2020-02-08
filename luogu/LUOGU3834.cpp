/**
* Number:p3834
* Title:【模板】可持久化线段树 1（主席树）
* Status:AC
* Tag:[可持久化, 主席树, 权值线段树]
* desc: 静态区间第k小
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
typedef unsigned long long ull;

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 2e5 + 10;

struct Node
{
    int sum, lc, rc; // 计数，左右儿子编号
} tree[MAXN * 20];
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
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
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