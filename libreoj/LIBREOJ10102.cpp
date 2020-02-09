/**
* Number:loj10102
* Title:「一本通 3.6 练习 3」旅游航道
* Status:AC
* Tag:[tarjan, 割边, 桥]
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

const int MAXN = 30010;
const int MAXM = 30010;
struct Edge
{
    int from, to, nxt;
} edges[MAXM * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

bool cut[MAXM * 2]; // cut[i]=true表示边i是割边
int dfn[MAXN], low[MAXN], dfsid;
void tarjan(int u, int pre)
{
    dfn[u] = low[u] = ++dfsid;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        if ((i ^ 1) == pre)
            continue; // 不直接走反向边
        int v = edges[i].to;
        if (!dfn[v])
        {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])            // 如果v不能绕到u或u的上方
                cut[i] = cut[i ^ 1] = true; // i是割边
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    while (readi(n, m) != EOF && n && m)
    {
        fill_n(head, n + 1, -1), edgeid = 0;
        while (m--)
        {
            int u, v;
            readi(u, v);
            addedge(u, v), addedge(v, u);
        }
        fill_n(cut, edgeid, false), fill_n(dfn, n + 1, 0), dfsid = 0;
        rep(i, 1, n) if (!dfn[i]) tarjan(i, -1);
        printf("%d\n", count(cut, cut + edgeid, true) / 2);
    }
    return 0;
}