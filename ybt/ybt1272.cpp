/**
* Number:ybt1272
* Title:分组背包
* Status:AC
* Tag:[分组背包]
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

int dp[104];
struct Item
{
    int w, c;
} items[14][34];
int tot[14];
int minw[14];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(minw, INF);
    int v, n, g;
    readi3(v, n, g);
    for (int i = 0; i < n; i++)
    {
        int w, c, p;
        readi3(w, c, p);
        Item &it = items[p][tot[p]++];
        it.w = w;
        it.c = c;
        minw[p] = min(minw[p], w);
    }
    for (int i = 1; i <= g; i++)
    {
        for (int j = v; j >= minw[i]; j--)
        {
            for (int k = 0; k < tot[i]; k++)
            {
                Item &it = items[i][k];
                if (j < it.w)
                    continue;
                dp[j] = max(dp[j], dp[j - it.w] + it.c);
            }
        }
    }
    printf("%d\n", dp[v]);
    return 0;
}