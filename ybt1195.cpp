/**
* Number:ybt1195
* Title:判断整除
* Status:AC
* Tag:[背包dp]
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

bool dp[10004][104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, k;
    scanf("%d %d", &n, &k);
    int t;
    scanf("%d", &t);
    dp[1][(t % k + k) % k] = true;
    for (int i = 2; i <= n; i++)
    {
        int t;
        scanf("%d", &t);
        t = abs(t);
        for (int j = 0; j < k; j++)
        {
            if (dp[i - 1][j])
            {
                dp[i][(j + t) % k] = true;
                dp[i][((j - t) % k + k) % k] = true;
            }
        }
    }
    if (dp[n][0])
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}