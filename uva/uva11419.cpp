/**
* Number:uva11419
* Title:SAM I AM
* Status:AC
* Tag:[二分图, hopcroft-karp, 最小点覆盖]
* desc: 一次可以消灭一行或一列网格中的敌人，最少几次可以消灭所有敌人
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

int dep[MAXN], maxdep;        // dep[]-路径长度 maxdep-findpath的最大深度
int match[MAXN];              // match[i]-i和谁匹配
bool vis[MAXN];               // Hungary算法中标记DFS树上的节点
bool findpath(int nx, int ny) // BFS搜索多条不相交的増广路
{
    static int Q[MAXN]; // 队列
    int L = 0, R = 0;   // L-队首 R-队尾
    fill_n(dep, nx + ny + 1, 0);
    for (int i = 1; i <= nx; i++)
        if (!match[i])
            dep[i] = 1, Q[R++] = i; // 从所有未匹配的点出发BFS
    maxdep = INF;
    for (int u = Q[L]; L < R && dep[u] <= maxdep; u = Q[++L])
    {
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].to;
            if (dep[v])
                continue;
            dep[v] = dep[u] + 1;
            if (!match[v])
                maxdep = dep[v]; // 每轮findpath时路径长度+1
            else
                dep[match[v]] = dep[v] + 1, Q[R++] = match[v];
        }
    }
    return maxdep != INF;
}
bool augment(int u) // Hungary算法
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (vis[v] || dep[v] != dep[u] + 1)
            continue;
        vis[v] = true;
        if (match[v] && dep[v] == maxdep)
            continue;
        if (!match[v] || augment(match[v]))
        {
            match[u] = v, match[v] = u;
            return true;
        }
    }
    return false;
}
int hopcroft_karp(int nx, int ny)
{
    int ans = 0;
    fill_n(match, nx + ny + 1, 0);
    while (findpath(nx, ny)) // 同时寻找多条不相交的増广路径
    {
        fill_n(vis, nx + ny + 1, false);
        for (int i = 1; i <= nx; i++)
            if (!match[i])
                ans += augment(i); // 沿着找到的路径増广
    }
    return ans;
}
void mincover(int nx, int ny) // nx-左支节点数量 ny-右支节点数量
{
    int maxmatch = hopcroft_karp(nx, ny);
    printf("%d\n", maxmatch);     // 输出最大匹配数
    findpath(nx, ny);             // 増广所有未匹配点，同Hungary算法求mincover的augment
    for (int i = 1; i <= nx; i++) // 输出匹配方案
        if (!dep[i])              // 选择了右部点后剩下的没有标记的左部点是覆盖点
            printf(" r%d", i);
    for (int i = 1; i <= ny; i++)
        if (dep[nx + i]) // 选择的右部的点
            printf(" c%d", i);
    puts("");
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
        clr(head, -1), edgeid = 0;
        repne(i, 0, n)
        {
            int x, y;
            readi(x, y);
            addedge(x, r + y); // 离散建图
        }
        mincover(r, c);
    }
    return 0;
}

/**
* Number:uva11419
* Title:SAM I AM
* Status:AC
* Tag:[二分图, hungary, 匈牙利算法, 最小点覆盖]
* desc: 一次可以消灭一行或一列网格中的敌人，最少几次可以消灭所有敌人
**/

/*
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

int match[MAXN];    // match[i]-与节点i匹配的是谁，0表示未匹配
bool vis[MAXN];     // 是否是DFS树上的节点
bool augment(int u) // 増广 u-DFS树的根节点
{
    vis[u] = true;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (vis[v])
            continue;
        vis[v] = true;
        if (!match[v] || augment(match[v]))
        {
            match[u] = v, match[v] = u;
            return true;
        }
    }
    return false;
}
int hungary(int nx, int ny) // nx-左支节点数量 ny-右支节点数量
{                           // 返回最大匹配数，匹配方案保存在match[]
    int ans = 0;
    fill_n(match, nx + ny + 1, 0);
    for (int i = 1; i <= nx; i++)
    {
        fill_n(vis, nx + ny + 1, false);
        ans += augment(i);
    }
    return ans;
}
void mincover(int nx, int ny) // nx-左支节点数量 ny-右支节点数量
{
    int maxmatch = hungary(nx, ny);
    printf("%d\n", maxmatch); // 输出最大匹配数
    fill_n(vis, nx + ny + 1, false);
    for (int i = 1; i <= nx; i++)
        if (!match[i])            // 左部没有匹配的点一定连接没有覆盖的边
            augment(i);           // 最小覆盖包含它右部有匹配的点
    for (int i = 1; i <= nx; i++) // 输出匹配方案
        if (!vis[i])              // 选择了右部点后剩下的没有标记的左部点是覆盖点
            printf(" r%d", i);
    for (int i = 1; i <= ny; i++)
        if (vis[nx + i]) // 选择的右部的点
            printf(" c%d", i);
    puts("");
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
            addedge(x, r + y); // 离散建图
        }
        mincover(r, c);
    }
    return 0;
}
*/