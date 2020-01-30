/**
* Number:ybt1197
* Title:山区建小学
* Status:AC
* Tag:[区间dp]
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

int dp[504][504];
int dis[504];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 1; i < m; i++)
    {
        scanf("%d", dis + i);
        dis[i] += dis[i - 1];
    }
    for (int i = 1; i < m; i++)
    {
        dp[i][1] = dp[i - 1][1] + dis[i] - dis[i >> 1];
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = i - 1; j < m; j++)
        {
            int cost = 0;
            int mincost = INF;
            for (int k = j; k >= i - 1; k--)
            {
                cost += dis[(k + j + 1) >> 1] - dis[k];
                if (dp[k - 1][i - 1] + cost < mincost)
                {
                    mincost = dp[k - 1][i - 1] + cost;
                }
            }
            dp[j][i] = mincost;
        }
    }
    printf("%d\n", dp[m - 1][n]);
    return 0;
}