/**
* Number:ybt1296
* Title:开餐馆
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

int m[104], p[104];
int dp[104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T;
    readi(T);
    while (T--)
    {
        int n, k;
        readi2(n, k);
        int ans = 0;
        for (int i = 0; i < n; i++)
            readi(m[i]);
        for (int i = 0; i < n; i++)
            readi(p[i]);
        for (int i = 0; i < n; i++)
        {
            int tmp = 0;
            for (int j = 0; j < i && m[i] - m[j] > k; j++)
                tmp = max(tmp, dp[j]);
            dp[i] = p[i] + tmp;
            ans = max(ans, dp[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}