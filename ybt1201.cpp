/**
* Number:ybt1201
* Title:菲波那契数列
* Status:AC
* Tag:[递推]
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

const int MAXN = 24;
ll dp[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    dp[1] = dp[2] = 1;
    for (int i = 3; i < MAXN; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int a;
        scanf("%d", &a);
        printf("%lld\n", dp[a]);
    }
    return 0;
}