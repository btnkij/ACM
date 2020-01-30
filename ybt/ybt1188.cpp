/**
* Number:ybt1188
* Title:菲波那契数列(2)
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

const int MAXN = 1e6 + 4;
int dp[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    dp[1] = dp[2] = 1;
    for (int i = 3; i < MAXN; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 1000;
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int a;
        scanf("%d", &a);
        printf("%d\n", dp[a]);
    }
    return 0;
}