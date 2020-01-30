/**
* Number:ybt1293
* Title:买书
* Status:AC
* Tag:[完全背包]
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

int w[] = {10, 20, 50, 100};
ll dp[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    dp[0] = 1;
    int n;
    readi(n);
    for (int i = 0; i < 4; i++)
    {
        for (int j = w[i]; j <= n; j++)
        {
            dp[j] += dp[j - w[i]];
        }
    }
    dp[0] = 0;
    printf("%lld\n", dp[n]);
    return 0;
}