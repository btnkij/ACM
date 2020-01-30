/**
* Number:ybt1292
* Title:宠物小精灵之收服
* Status:AC
* Tag:[二维01背包]
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

int dp[1010][510];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, k;
    readi3(n, m, k);
    int c = 0, r = 0;
    while (k--)
    {
        int w1, w2;
        readi2(w1, w2);
        for (int i = n; i >= w1; i--)
        {
            for (int j = m; j >= w2; j--)
            {
                if (dp[i][j] < dp[i - w1][j - w2] + 1)
                {
                    dp[i][j] = dp[i - w1][j - w2] + 1;
                }
            }
        }
    }
    for (int i = n; i >= 0; i--)
    {
        for (int j = m; j >= 0; j--)
        {
            if (dp[i][j] > c || (dp[i][j] == c && m - j > r))
            {
                c = dp[i][j];
                r = m - j;
            }
        }
    }
    printf("%d %d\n", c, r);
    return 0;
}