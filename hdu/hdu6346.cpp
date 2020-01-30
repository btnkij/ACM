/**
* Number:hdu6346
* Title:整数规划
* Status:AC
* Tag:[KM, 二分图, 最大完备匹配]
* desc: n阶方阵a[i][j]，求max(sum(x[i])+sum(y[i])) s.t. x[i]+y[j]<=a[i][j]
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

const int MAXN = 210;
int n;                 // 邻接矩阵大小
ll adj[MAXN][MAXN];    // 邻接矩阵
ll lx[MAXN], ly[MAXN]; // 顶标，满足lx[u]+ly[v]==adj[u][v]
ll slack[MAXN];
bool visy[MAXN];
int pre[MAXN];
int match[MAXN];      // 与右侧v匹配的是match[v]
void augment(int src) // BFS増广
{
    fill_n(visy, n + 1, false);
    fill_n(slack, n + 1, INF);
    int y = 0;
    match[0] = src;
    do
    {
        visy[y] = true;
        int u = match[y], tmpy;
        ll delta = INF;
        for (int v = 1; v <= n; v++)
        {
            if (visy[v])
                continue;
            if (lx[u] + ly[v] - adj[u][v] < slack[v])
                slack[v] = lx[u] + ly[v] - adj[u][v], pre[v] = y;
            if (slack[v] < delta)
                delta = slack[v], tmpy = v;
        }
        for (int v = 0; v <= n; v++)
        {
            if (visy[v])
                lx[match[v]] -= delta, ly[v] += delta;
            else
                slack[v] -= delta;
        }
        y = tmpy;
    } while (~match[y]);
    for (; y; y = pre[y])
        match[y] = match[pre[y]];
}
ll km() // 返回最大匹配权值，match为匹配结果
{
    rep(i, 1, n) lx[i] = *max_element(adj[i] + 1, adj[i] + n + 1);
    fill_n(ly, n + 1, 0);
    fill_n(match, n + 1, -1);
    rep(i, 1, n) augment(i);
    ll ans = 0;
    rep(i, 1, n) ans += lx[i] + ly[i];
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T;
    readi(T);
    rep(kase, 1, T)
    {
        readi(n); // 方阵阶数
        rep2(i, 1, n, j, 1, n)
        {
            int w;
            readi(w);
            adj[i][j] = -w; // 取反，求最小匹配
        }
        ll ans = km();
        printf("Case #%d: %lld\n", kase, -ans);
    }
    return 0;
}