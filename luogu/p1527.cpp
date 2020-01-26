/**
* Number:p1527
* Title:[国家集训队]矩阵乘法
* Status:AC
* Tag:[整体二分]
* desc:静态矩阵第k小
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

#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

inline int read()
{
    register int num = 0;
    register char ch;
    register bool sign = false;
    do
    {
        ch = getchar();
        if (ch == '-')
            sign = true;
    } while (ch < '0' || ch > '9');
    do
    {
        num = (num << 3) + (num << 1) + (ch & 0xF);
        ch = getchar();
    } while ('0' <= ch && ch <= '9');
    if (sign)
        num = -num;
    return num;
}

// 二维树状数组模板
int n, tree[510][510]; // n-方阵的阶数
inline int lowbit(int x)
{
    return x & -x;
}
void add(int x, int y, int val)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            tree[i][j] += val;
}
int query(int x, int y)
{
    int ans = 0;
    for (int i = x; i; i ^= lowbit(i))
        for (int j = y; j; j ^= lowbit(j))
            ans += tree[i][j];
    return ans;
}

struct Node
{
    int x, y, val; // 行，列，值
    bool operator<(const Node &rhs) const
    {
        return val < rhs.val;
    }
} nodes[510 * 510]; // 按坐标存储矩阵
struct Query
{
    int x1, y1, x2, y2, k, id;
} querys[60010], ql[60010], qr[60010]; // querys-全部询问，ql/qr-buffer
int ans[60010], qltail, qrtail;
// 整体二分，[nbeg,nend)是答案的范围，[qbeg,qend)是询问的范围
void solve(int nbeg, int nend, int qbeg, int qend)
{
    if (qbeg >= qend) // 如果询问为空
        return;
    if (nbeg + 1 == nend) // 如果答案已经确定
    {
        repne(i, qbeg, qend) ans[querys[i].id] = nodes[nbeg].val;
        return;
    }
    int nmid = (nbeg + nend) >> 1;
    for (int i = nbeg; i < nmid; i++) // 二分答案，标记前一半元素
        add(nodes[i].x, nodes[i].y, 1);
    qltail = qrtail = 0;
    for (int i = qbeg; i < qend; i++)
    {
        Query &q = querys[i];
        // 统计询问的子矩阵中被标记的元素个数
        int cnt = query(q.x2, q.y2) - query(q.x1 - 1, q.y2) - query(q.x2, q.y1 - 1) + query(q.x1 - 1, q.y1 - 1);
        if (cnt >= q.k)
            ql[qltail++] = q;
        else
        {
            q.k -= cnt;
            qr[qrtail++] = q;
        }
    }
    int qmid = copy(ql, ql + qltail, querys + qbeg) - querys;
    copy(qr, qr + qrtail, querys + qmid);
    for (int i = nbeg; i < nmid; i++) // 还原树状数组
        add(nodes[i].x, nodes[i].y, -1);
    solve(nbeg, nmid, qbeg, qmid);
    solve(nmid, nend, qmid, qend);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int q;
    n = read(), q = read(); // 方阵阶数，询问个数
    int tot = 0;
    rep2(i, 1, n, j, 1, n)
    {
        nodes[tot].x = i, nodes[tot].y = j;
        nodes[tot++].val = read();
    }
    sort(nodes, nodes + tot); // 排序矩阵元素
    repne(i, 0, q)
    {
        Query &t = querys[i];
        t.x1 = read(), t.y1 = read();
        t.x2 = read(), t.y2 = read();
        t.k = read();
        t.id = i;
    }
    solve(0, tot, 0, q); // 整体二分
    repne(i, 0, q) printf("%d\n", ans[i]);
    return 0;
}