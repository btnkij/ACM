/**
* Number:uva11383
* Title:Golden Tiger Claw
* Status:AC
* Tag:[二分图, km, 完美匹配]
* desc: 已知方阵M，求min{sum(r[i])+sum(c[j])} s.t. M[i][j]<=r[i]+c[j]
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
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
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