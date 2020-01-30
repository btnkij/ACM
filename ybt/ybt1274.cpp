/**
* Number:ybt1274
* Title:合并石子
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))

int sum[104];
int dp[104][104]; // dp[left][right]
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
        readi(sum[i]);
        sum[i] += sum[i - 1];
    }
    for (int L = 2; L <= n; L++)
    {
        for (int lt = 1, rt = lt + L - 1; rt <= n; lt++, rt++)
        {
            int tmp = INF;
            for (int k = lt; k < rt; k++)
                tmp = min(tmp, dp[lt][k] + dp[k + 1][rt]);
            dp[lt][rt] = tmp + sum[rt] - sum[lt - 1];
        }
    }
    printf("%d\n", dp[1][n]);
    return 0;
}