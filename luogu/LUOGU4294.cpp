/**
* Number:luogu4294
* Title:[WC2008]游览计划
* Status:AC
* Tag:[斯坦纳树, steiner-tree]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <tuple>
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

const int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int w[15][15], dp[15][15][1 << 12]; // w-权值
tuple<int, int, int> pre[15][15][1 << 12]; // pre-状态转移的前驱
void steiner1(int n, int m, int sta) // 状压DP，合并子斯坦纳树
{
    rep2(x, 1, n, y, 1, m)
    {
        auto f = dp[x][y];
        for (int sub = sta; sub; sub = (sub - 1) & sta)
        {
            if (f[sta] > f[sub] + f[sta ^ sub] - w[x][y])
            {
                f[sta] = f[sub] + f[sta ^ sub] - w[x][y];
                pre[x][y][sta] = {x, y, sub};
            }
        }
    }
}
void steiner2(int n, int m, int sta) // SPFA顺序的DP，更新周围点的状态
{
    static queue<pair<int, int>> Q;
    static bool vis[15][15];
    rep2(x, 1, n, y, 1, m)
    {
        if (dp[x][y][sta] != INF)
        {
            Q.emplace(x, y);
            vis[x][y] = true;
        }
    }
    while (!Q.empty())
    {
        int x = Q.front().first, y = Q.front().second;
        Q.pop();
        vis[x][y] = false;
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dir[i][0], yy = y + dir[i][1];
            if (w[xx][yy] == -1)
                continue;
            if (dp[xx][yy][sta] > dp[x][y][sta] + w[xx][yy])
            {
                dp[xx][yy][sta] = dp[x][y][sta] + w[xx][yy];
                pre[xx][yy][sta] = {x, y, sta};
                if (!vis[xx][yy])
                {
                    Q.emplace(xx, yy);
                    vis[xx][yy] = true;
                }
            }
        }
    }
}

char plan[15][15];
void dfs(int x, int y, int sta) // 输出解
{
    if (!sta)
        return;
    plan[x][y] = w[x][y] ? 'o' : 'x';
    int prex, prey, pres;
    tie(prex, prey, pres) = pre[x][y][sta];
    dfs(prex, prey, pres);
    if (prex == x && prey == y) // 如果由自身DP转移而来，分别DFS两边的子树
        dfs(prex, prey, sta ^ pres);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m); // n-行数 m-列数
    clr(w, -1), clr(dp, INF);
    int tot = 0;
    rep2(i, 1, n, j, 1, m)
    {
        readi(w[i][j]);
        if (w[i][j] == 0)
        {
            dp[i][j][1 << (tot++)] = 0;
        }
    }
    int all = (1 << tot) - 1;
    for (int sta = 1; sta <= all; sta++) // 枚举所有连通状态
    {
        steiner1(n, m, sta); // 合并自身
        steiner2(n, m, sta); // 更新周围
    }
    int ans = INF, sx, sy;
    rep2(i, 1, n, j, 1, m) // 找根节点
    {
        if (dp[i][j][all] < ans)
        {
            ans = dp[i][j][all];
            sx = i, sy = j;
        }
    }
    printf("%d\n", ans);
    dfs(sx, sy, all);
    rep2(i, 1, n, j, 1, m) if (!plan[i][j]) plan[i][j] = '_';
    rep(i, 1, n) puts(plan[i] + 1);
    return 0;
}