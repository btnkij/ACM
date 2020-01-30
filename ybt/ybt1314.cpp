/**
* Number:ybt1314
* Title:过河卒(Noip2002)
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

ll dp[24][24];
int dir[][2] = {{0, 0}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int bx, by, cx, cy;
    scanf("%d %d %d %d", &bx, &by, &cx, &cy);
    dp[0][0] = 1;
    for (int i = 0; i < 9; i++)
    {
        int xx = cx + dir[i][0];
        int yy = cy + dir[i][1];
        if (0 <= xx && 0 <= yy)
        {
            dp[xx][yy] = -1;
        }
    }
    for (int ix = 0; ix <= bx; ix++)
    {
        for (int iy = 0; iy <= by; iy++)
        {
            if (dp[ix][iy] == -1)
                dp[ix][iy] = 0;
            else
            {
                if (ix > 0)
                    dp[ix][iy] += dp[ix - 1][iy];
                if (iy > 0)
                    dp[ix][iy] += dp[ix][iy - 1];
            }
        }
    }
    printf("%lld\n", dp[bx][by]);
    return 0;
}