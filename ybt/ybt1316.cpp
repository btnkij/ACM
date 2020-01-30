/**
* Number:ybt1316
* Title:数的计数(Noip2001)
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

int dp[1004];
int sum[1004];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    dp[1] = sum[1] = 1;
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        dp[i] = sum[i >> 1] + 1;
        sum[i] = sum[i - 1] + dp[i];
    }
    printf("%d\n", dp[n]);
    return 0;
}