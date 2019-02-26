/**
* Number:ybt1258
* Title:数字金字塔
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

int dp1[1010], dp2[1010];
int *pcur, *pnxt;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int nrow;
    readi(nrow);
    pcur = dp1, pnxt = dp2;
    readi(pcur[1]);
    for (int i = 2; i <= nrow; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            readi(pnxt[j]);
        }
        pnxt[1] += pcur[1];
        for (int j = 2; j < i; j++)
            pnxt[j] += max(pcur[j], pcur[j - 1]);
        pnxt[i] += pcur[i - 1];
        swap(pcur, pnxt);
    }
    int ans = *max_element(pcur + 1, pcur + nrow + 1);
    printf("%d\n", ans);
    return 0;
}