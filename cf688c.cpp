/**
* Number:cf688c
* Title:NP-Hard Problem
* Status:AC
* Tag:[并查集, 二分图判定]
* desc: 判定一个图是否是二分图，输出左右支的节点
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

int fa[100100], rel[100100]; // 父节点，与父节点的关系
int findr(int x)
{
    if (x == fa[x])
        return x;
    int rx = findr(fa[x]);
    rel[x] = rel[x] ^ rel[fa[x]];
    return fa[x] = rx;
}
bool merge(int x, int y, int r)
{
    int rx = findr(x), ry = findr(y);
    if (rx == ry)
        return (rel[x] ^ rel[y]) == r;
    rel[rx] = rel[x] ^ rel[y] ^ r;
    fa[rx] = ry;
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m);            // 节点数，边数
    rep(i, 1, n) fa[i] = i; // 并查集的初始化
    while (m--)
    {
        int u, v;
        readi(u, v);         // (u, v)无向边
        if (!merge(u, v, 1)) // 合并时出现矛盾
        {
            puts("-1"); // 不是二分图
            return 0;
        }
    }
    rep(i, 1, n) findr(i); // 更新fa[]和rel[]
    int cnt = count(rel + 1, rel + n + 1, 0);
    printf("%d\n", cnt);
    rep(i, 1, n) if (rel[i] == 0) printf("%d ", i); // 左支
    printf("\n%d\n", n - cnt);
    rep(i, 1, n) if (rel[i] == 1) printf("%d ", i); // 右支
    return 0;
}