/**
* Number:loj10097
* Title:「一本通 3.5 练习 5」和平委员会
* Status:AC
* Tag:[2-sat, tarjan]
* desc: n个党派，2n个代表，2i-1和2i属于一个党派，m对代表不能共存，输出每个党派选一名代表的方案
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

const int MAXN = 8010;
const int MAXM = 20010;
struct Edge
{
    int from, to, nxt;
} edges[MAXM * 4];
int head[MAXN * 2], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

int dfn[MAXN * 2], low[MAXN * 2], dfsid;
int grp[MAXN * 2], grpid;
vector<int> trace;
void tarjan(int u) // Tarjan强连通分量模板
{
    dfn[u] = low[u] = ++dfsid;
    trace.push_back(u);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (!dfn[v])
            tarjan(v);
        if (!grp[v])
            low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u])
    {
        for (grp[u] = ++grpid; trace.back() != u; trace.pop_back())
            grp[trace.back()] = grpid;
        trace.pop_back();
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi(n, m);
    clr(head, -1), edgeid = 0;
    repne(i, 0, m)
    {
        int u, v;
        readi(u, v);       // u和v不能同时选
        u--, v--;          // 从0开始计数，与u同属一个党派的是u^1
        addedge(u, v ^ 1); // 选了u就必须选v^1
        addedge(v, u ^ 1); // 选了v就必须选u^1
        // 不能推出 u^1->v, v^1->u 这些关系
    }
    repne(i, 0, n << 1) if (!dfn[i]) tarjan(i);
    for (int i = 0; i < (n << 1); i += 2)
    {
        if (grp[i] == grp[i ^ 1]) // 出现矛盾，i与i^1在同一连通分量中
        {
            puts("NIE"); // 无解
            return 0;
        }
    }
    for (int i = 0; i < (n << 1); i++)
    {
        if (grp[i] < grp[i ^ 1])   // 可能存在i^1->i的路径
        {                          // 如果选了i^1，那么i也必须选
            printf("%d\n", i + 1); // 所以只能选i，输出时记得+1
        }
    }
    return 0;
}