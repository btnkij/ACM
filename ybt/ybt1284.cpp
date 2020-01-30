/**
* Number:ybt1284
* Title:摘花生
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
    int T;
    readi(T);
    while (T--)
    {
        int r, c;
        readi2(r, c);
        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                readi(dp[i][j]);
                dp[i][j] += max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        printf("%d\n", dp[r][c]);
    }
    return 0;
}