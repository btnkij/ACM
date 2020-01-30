/**
* Number:ybt1271
* Title:潜水员
* Status:AC
* Tag:[二维, 01背包]
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

int dp[24][84];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(dp, INF);
    dp[0][0] = 0;
    int m, n, k;
    readi3(m, n, k);
    for (int i = 0; i < k; i++)
    {
        int a, b, c;
        readi3(a, b, c);
        for (int jm = m; jm >= 0; jm--)
        {
            for (int jn = n; jn >= 0; jn--)
            {
                if (dp[jm][jn] != INF)
                {
                    int jma = min(m, jm + a);
                    int jnb = min(n, jn + b);
                    dp[jma][jnb] = min(dp[jma][jnb], dp[jm][jn] + c);
                }
            }
        }
    }
    printf("%d\n", dp[m][n]);
    return 0;
}