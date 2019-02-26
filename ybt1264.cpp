/**
* Number:ybt1264
* Title:合唱队形
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

int h[110];
int dpfor[110], dpback[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    for (int i = 0; i < n; i++)
        readi(h[i]);
    for (int i = 0; i < n; i++)
    {
        dpfor[i] = 1;
        for (int j = 0; j < i; j++)
        {
            if (h[j] < h[i] && dpfor[j] + 1 > dpfor[i])
                dpfor[i] = dpfor[j] + 1;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        dpback[i] = 1;
        for (int j = n - 1; j > i; j--)
        {
            if (h[j] < h[i] && dpback[j] + 1 > dpback[i])
                dpback[i] = dpback[j] + 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, dpfor[i] + dpback[i] - 1);
    }
    printf("%d\n", n - ans);
    return 0;
}