/**
* Number:ybt1263
* Title:友好城市
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

struct Seg
{
    int a, b;
    bool operator<(const Seg &rhs) const
    {
        return a < rhs.a;
    }
} segs[5010];
int dp[5010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    for (int i = 0; i < n; i++)
    {
        int a, b;
        readi2(a, b);
        segs[i].a = a;
        segs[i].b = b;
    }
    sort(segs, segs + n);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp = 0;
        for (int j = 0; j < i; j++)
        {
            if (segs[i].a > segs[j].a && segs[i].b > segs[j].b)
            {
                tmp = max(tmp, dp[j]);
            }
        }
        dp[i] = tmp + 1;
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}