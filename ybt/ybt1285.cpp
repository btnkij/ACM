/**
* Number:ybt1285
* Title:最大上升子序列和
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

int num[1004];
int dp[1004];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    int ans = -INF;
    for (int i = 0; i < n; i++)
    {
        readi(num[i]);
        int t = 0;
        for (int j = 0; j < i; j++)
        {
            if (num[i] > num[j])
                t = max(t, dp[j]);
        }
        dp[i] = t + num[i];
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}