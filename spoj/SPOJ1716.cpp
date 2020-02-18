/**
* Number:spoj1716
* Title:GSS3 - Can you answer these queries III
* Status:AC
* Tag:[动态DP, 线段树, 矩阵]
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

const int MAXN = 5e4 + 10;
int a[MAXN];
struct Node
{
    int dp[3][3];
    Node() // 初始化为乘法零元
    {
        dp[0][0] = 0, dp[0][1] = -INF, dp[0][2] = -INF;
        dp[1][0] = -INF, dp[1][1] = 0, dp[1][2] = -INF;
        dp[2][0] = -INF, dp[2][1] = -INF, dp[2][2] = 0;
    }
    Node(int val)
    {
        dp[0][0] = val, dp[0][1] = -INF, dp[0][2] = val;
        dp[1][0] = val, dp[1][1] = 0, dp[1][2] = val;
        dp[2][0] = -INF, dp[2][1] = -INF, dp[2][2] = 0;
    }
    Node operator*(const Node &rhs) const // 定义乘法运算c[i][j]=max(a[i][k]+b[k][j])
    {
        Node ans(-INF);
        rep2(i, 0, 2, j, 0, 2)
        {
            int &f = ans.dp[i][j];
            rep(k, 0, 2) f = max(f, dp[i][k] + rhs.dp[k][j]);
        }
        return ans;
    }
} tree[MAXN * 4]; // 线段树模板：维护区间矩阵乘积
void pushup(int p)
{
    tree[p] = tree[p << 1] * tree[p << 1 | 1];
}
void build(int p, int lt, int rt)
{
    if (lt == rt)
    {
        tree[p] = Node(a[lt]);
        return;
    }
    int mid = (lt + rt) >> 1;
    build(p << 1, lt, mid);
    build(p << 1 | 1, mid + 1, rt);
    pushup(p);
}
void update(int p, int lt, int rt, int qpos, int qval)
{
    if (lt == rt)
    {
        tree[p] = Node(qval);
        return;
    }
    int mid = (lt + rt) >> 1;
    if (qpos <= mid)
        update(p << 1, lt, mid, qpos, qval);
    else
        update(p << 1 | 1, mid + 1, rt, qpos, qval);
    pushup(p);
}
Node query(int p, int lt, int rt, int qlt, int qrt)
{
    if (qlt <= lt && rt <= qrt)
        return tree[p];
    int mid = (lt + rt) >> 1;
    Node ans;
    if (qlt <= mid)
        ans = ans * query(p << 1, lt, mid, qlt, qrt);
    if (mid < qrt)
        ans = ans * query(p << 1 | 1, mid + 1, rt, qlt, qrt);
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n); // 序列长度
    rep(i, 1, n) readi(a[i]);
    build(1, 1, n); // 建线段树
    int q;
    readi(q); // 询问数
    while (q--)
    {
        int op, x, y;
        readi(op, x, y);
        if (op == 0) // 修改a[x]的值为y
        {
            update(1, 1, n, x, y);
        }
        else if (op == 1) // 查询[x,y]的最大子串和
        {
            Node ans = query(1, 1, n, x, y);
            printf("%d\n", ans.dp[1][2]); // ans*[f0 g0 0]^T
        }
    }
    return 0;
}