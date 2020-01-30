/**
* Number:ybt1262 
* Title:挖地雷
* Status:AC
* Tag:[dp]
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
#define PI acos(-1)
typedef long long ll;

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))

int num[210];
int dp[210], pre[210];
void showpath(int x)
{
    if (pre[x])
        showpath(pre[x]);
    if (pre[x])
        putchar('-');
    printf("%d", x);
}
struct Edge
{
    int from, to;
    bool operator<(const Edge &rhs) const
    {
        return from < rhs.from;
    }
} edges[210 * 210];
int tot;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    for (int i = 1; i <= n; i++)
    {
        readi(num[i]);
        dp[i] = num[i];
    }
    int from, to;
    while (readi2(from, to) != EOF && from && to)
    {
        edges[tot].from = from;
        edges[tot].to = to;
        tot++;
    }
    sort(edges, edges + tot);
    for (int i = 0; i < tot; i++)
    {
        int from = edges[i].from;
        int to = edges[i].to;
        if (dp[to] <= dp[from] + num[to])
        {
            pre[to] = from;
            dp[to] = dp[from] + num[to];
        }
    }
    int idx = max_element(dp + 1, dp + n + 1) - dp;
    showpath(idx);
    printf("\n%d\n", dp[idx]);
    return 0;
}