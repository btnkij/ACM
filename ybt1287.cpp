/**
* Number:ybt1287
* Title:最低通行费
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

int dp[104][104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            readi(dp[i][j]);
            int tmp = INF;
            if (i > 0)
                tmp = min(tmp, dp[i - 1][j]);
            if (j > 0)
                tmp = min(tmp, dp[i][j - 1]);
            if (tmp == INF)
                tmp = 0;
            dp[i][j] += tmp;
        }
    }
    printf("%d\n", dp[n - 1][n - 1]);
    return 0;
}