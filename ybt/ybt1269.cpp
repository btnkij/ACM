/**
* Number:ybt1269
* Title:庆功会
* Status:AC
* Tag:[多重背包]
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

int dp[6010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    readi2(n, m);
    for (int i = 0; i < n; i++)
    {
        int w, c, s;
        readi3(w, c, s);
        int ss = 1;
        while (s)
        {
            ss = min(ss, s);
            int ww = w * ss;
            int cc = c * ss;
            for (int j = m; j >= ww; j--)
            {
                dp[j] = max(dp[j], dp[j - ww] + cc);
            }
            s -= ss;
            ss <<= 1;
        }
    }
    printf("%d\n", dp[m]);
    return 0;
}