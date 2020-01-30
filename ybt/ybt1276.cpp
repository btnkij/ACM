/**
* Number:ybt1276
* Title:编辑距离
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

char s1[2004], s2[2004];
int dp[2004][2004];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s1 + 1);
    reads(s2 + 1);
    int len1 = strlen(s1 + 1);
    int len2 = strlen(s2 + 1);
    for (int i = 0; i <= len1; i++)
    {
        for (int j = 0; j <= len2; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = i + j;
                continue;
            }
            if (s1[i] == s2[j])
                dp[i][j] = dp[i - 1][j - 1];
            else
            {
                int tmp = INF;
                tmp = min(tmp, dp[i - 1][j - 1]);
                tmp = min(tmp, dp[i - 1][j]);
                tmp = min(tmp, dp[i][j - 1]);
                dp[i][j] = tmp + 1;
            }
        }
    }
    printf("%d\n", dp[len1][len2]);
    return 0;
}