/**
* Number:ybt1297
* Title:公共子序列
* Status:AC
* Tag:[记忆化搜索]
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

char s1[204], s2[204];
int dp[204][204];
bool vis[204][204];
int solve(int i1, int i2)
{
    if (s1[i1] == '\0' || s2[i2] == '\0')
        return 0;
    if (vis[i1][i2])
        return dp[i1][i2];
    vis[i1][i2] = true;
    int &ans = dp[i1][i2];
    if (s1[i1] == s2[i2])
        return ans = solve(i1 + 1, i2 + 1) + 1;
    return ans = max(solve(i1 + 1, i2), solve(i1, i2 + 1));
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(scanf("%s %s",s1,s2)!=EOF)
    {
        mset(vis,false);
        int ans = solve(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}