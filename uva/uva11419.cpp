/**
* Number:uva11419
* Title:SAM I AM
* Status:AC
* Tag:[二分图, hungary, 匈牙利算法, 最小点覆盖]
* desc: 一次可以消灭一行或一列网格中的敌人，最少几次可以消灭所有敌人
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
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
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