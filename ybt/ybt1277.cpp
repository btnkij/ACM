/**
* Number:ybt1277
* Title:方格取数
* Status:AC
* Tag:[dp, 四维]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int dp[12][12][12][12];
int mat[12][12];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    int x, y, v;
    while (readi3(x, y, v) != EOF && x && y && v)
    {
        mat[x][y] = v;
    }
    rep2(x1, 1, n, y1, 1, n)
    {
        rep2(x2, 1, n, y2, 1, n)
        {
            dp[x1][y1][x2][y2] =
                max(
                    max(dp[x1 - 1][y1][x2 - 1][y2], dp[x1][y1 - 1][x2][y2 - 1]),
                    max(dp[x1][y1 - 1][x2 - 1][y2], dp[x1 - 1][y1][x2][y2 - 1])
                ) + ((x1 == x2 && y1 == y2) ? mat[x1][y1] : mat[x1][y1] + mat[x2][y2]);
        }
    }
    printf("%d\n", dp[n][n][n][n]);
    return 0;
}