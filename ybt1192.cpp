/**
* Number:ybt1192
* Title:放苹果
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

ll dfs(int m, int n, int pre)
{
    if (m == 0 || n == 1)
        return 1;
    int lb = (m + n - 1) / n;
    ll ans = 0;
    for (int i = min(m, pre); i >= lb; i--)
    {
        ans += dfs(m - i, n - 1, i);
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int m, n;
        scanf("%d %d", &m, &n);
        printf("%lld\n", dfs(m, n, m));
    }
    return 0;
}