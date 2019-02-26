/**
* Number:ybt1260
* Title:拦截导弹(Noip1999)
* Status:?
* Tag:[]
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

int num[1010], tot;
int up[1010], totu;
int down[1010], totd;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int t;
    while (readi(t) != EOF)
        num[tot++] = t;
    for (int i = 0; i < tot; i++)
    {
        t = totd;
        while (t > 0 && down[t - 1] < num[i])
            t--;
        down[t] = num[i];
        totd = max(totd, t + 1);
        t = totu;
        while (t > 0 && up[t - 1] >= num[i])
            t--;
        up[t] = num[i];
        totu = max(totu, t + 1);
    }
    printf("%d\n%d\n", totd, totu);
    return 0;
}