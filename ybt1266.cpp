/**
* Number:ybt1266
* Title:机器分配
* Status:AC
* Tag:[记忆化搜索]
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

int n, m;
bool vis[20][20];
int dp[20][20], pre[20][20];
int adj[20][20];
int solve(int idx, int remain)
{
    if (idx > n || remain <= 0)
        return 0;
    if (vis[idx][remain])
        return dp[idx][remain];
    vis[idx][remain] = true;
    int &ans = dp[idx][remain];
    for (int i = 0; i <= remain; i++)
    {
        int tmp = adj[idx][i] + solve(idx + 1, remain - i);
        if (ans < tmp)
        {
            ans = tmp;
            pre[idx][remain] = i;
        }
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(n, m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            readi(adj[i][j]);
        }
    }
    int ans = solve(1, m);
    printf("%d\n", ans);
    int r = m;
    for (int i = 1; i <= n; i++)
    {
        printf("%d %d\n", i, pre[i][r]);
        r -= pre[i][r];
    }
    return 0;
}