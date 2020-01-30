/**
* Number:ybt1295
* Title:装箱问题
* Status:AC
* Tag:[01背包]
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

bool dp[20010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    dp[0] = true;
    int v, n;
    readi2(v, n);
    int ans = 0;
    while (n--)
    {
        int w;
        readi(w);
        for (int i = v; i >= w; i--)
        {
            dp[i] = dp[i] || dp[i - w];
            if (dp[i])
                ans = max(ans, i);
        }
    }
    printf("%d\n", v - ans);
    return 0;
}