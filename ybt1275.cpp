/**
* Number:ybt1275
* Title:乘积最大
* Status:AC
* Tag:[dfs]
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

char num[16];
int n, k;
ll ans;
void dfs(ll prod, int pre, int dep)
{
    // printf("%lld %d %d\n", prod, pre, dep);
    if (prod == 0 || dep == k + 1)
    {
        ans = max(ans, prod);
        return;
    }
    for (int i = pre + 1; i < n && n - i >= k + 1 - dep; i++)
    {
        ll m = 0;
        for (int j = pre + 1; j <= i; j++)
        {
            m = m * 10 + (num[j] & 0xF);
        }
        dfs(prod * m, i, dep + 1);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(n, k);
    reads(num);
    dfs(1, -1, 0);
    printf("%lld\n", ans);
    return 0;
}