/**
* Number:luogu4716
* Title:【模板】最小树形图
* Status:AC
* Tag:[最小树形图, 朱-刘算法]
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

const int MAXN = 110;
const int MAXM = 10010;
struct Edge
{
    int from, to, dis;
} edges[MAXM];

int inw[MAXN], pre[MAXN], grp[MAXN], vis[MAXN];
int zhu_liu(int n, int m, int root) // 朱-刘算法 n-节点数 m-边数 root-根
{
    int ans = 0;
    while (true)
    {
        fill_n(inw, n + 1, INF), inw[root] = 0; // 每个点入边的最小边权
        for (int i = 0; i < m; i++)
        {
            Edge &e = edges[i];
            if (e.from != e.to && e.dis < inw[e.to]) // 跳过被缩掉的边
                pre[e.to] = e.from, inw[e.to] = e.dis;
        }
        if (find(inw + 1, inw + n + 1, INF) != inw + n + 1) // 如果不连通
            return -1;                                      // 无解
        int grpid = 0;
        fill_n(grp, n + 1, 0), fill_n(vis, n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            ans += inw[i];
            int x = i;
            while (x != root && !grp[x] && vis[x] != i)
                vis[x] = i, x = pre[x];
            if (x != root && !grp[x]) // 如果有环，缩为一个点
            {
                grp[x] = ++grpid;
                for (int y = pre[x]; y != x; y = pre[y])
                    grp[y] = grpid;
            }
        }
        if (grpid == 0) // 如果无环，计算结束
            break;
        for (int i = 1; i <= n; i++) // 否则重新建图
            if (!grp[i])
                grp[i] = ++grpid; // 其他节点的新编号
        for (int i = 0; i < m; i++)
        {
            Edge &e = edges[i];
            int t = inw[e.to];
            e.from = grp[e.from], e.to = grp[e.to]; // 更新边
            if (e.from != e.to)
                e.dis -= t; // 更新边权
        }
        n = grpid, root = grp[root];
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, root;
    readi(n, m, root); // n-节点数 m-边数 root-根
    repne(i, 0, m) readi(edges[i].from, edges[i].to, edges[i].dis);
    printf("%d", zhu_liu(n, m, root));
    return 0;
}