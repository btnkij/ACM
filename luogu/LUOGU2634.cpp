/**
* Number:p2634
* Title:[国家集训队]聪聪可可
* Status:AC
* Tag:[点分治]
* desc: 树上选一条链，求边权和是3的倍数的概率
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

int root, maxrk, rk[MAXN], totrk; // rk[]-子树的秩 totrk-当前子树的节点数
bool cg[MAXN];                    // 是否是分治过的重心
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
    tmp = max(tmp, totrk - rk[u]);
    if (tmp < maxrk)
        root = u, maxrk = tmp;
}
int a, b;                         // 是3的倍数的方案数，总方案数
int allcnt[4], cnt[4];            // 之前所有子树中、当前子树中模3为i的方案数
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
void solve(int u, int totrk) // u-子树中任意点 totrk-子树的总节点数
{
    maxrk = INF, ::totrk = totrk; // 注意getcg前的全局变量初始化
    getcg(u, -1);
    cg[u = root] = true; // root是全局变量，为防止被修改，getcg后将root复制给u
    clr(allcnt, 0);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (cg[v])
            continue;
        clr(cnt, 0);
        dfs(v, edges[i].w, -1);
        for (int i = 0; i < 3; i++)
            allcnt[i] += cnt[i];
    }
    for (int i = head[u]; ~i; i = edges[i].nxt) // 分治root的每个子树
    {
        int v = edges[i].to;
        if (cg[v])
            continue;
        if (rk[v] > rk[u]) // root上方的子树rk不正确，需在这里修正
            rk[v] = totrk - rk[u];
        solve(v, rk[v]);
    }
}

int gcd(int a, int b) // GCD模板
{
    return b == 0 ? a : gcd(b, a % b);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n); // 节点数
    clr(head, -1), edgeid=0; // 链式前向星的初始化
    repne(i, 1, n)
    {
        int x, y, w;
        readi(x, y, w); // 边的起点，终点，权值
        addedge(x, y, w), addedge(y, x, w);
    }
    solve(1, n); // 点分治
    b = n * n;
    a = a * 2 + n;
    int d = gcd(a, b);
    printf("%d/%d", a / d, b / d);
    return 0;
}