/**
* Number:ybt1194
* Title:移动路线
* Status:AC
* Tag:[排列组合]
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

int factor[100];
ll comb(int a, int b)
{
    for (int aa = a - b + 1; aa <= a; aa++)
    {
        int tmp = aa;
        for (int i = 2; i * i <= tmp; i++)
        {
            while (tmp % i == 0)
            {
                factor[i]++;
                tmp /= i;
            }
        }
        if (tmp > 1)
            factor[tmp]++;
    }
    for (int bb = 2; bb <= b; bb++)
    {
        int tmp = bb;
        for (int i = 2; i * i <= tmp; i++)
        {
            while (tmp % i == 0)
            {
                factor[i]--;
                tmp /= i;
            }
        }
        if (tmp > 1)
            factor[tmp]--;
    }
    ll ans = 1;
    for (int i = 2; i <= a; i++)
    {
        if (factor[i])
            ans *= pow((ll)i, factor[i]);
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m, n;
    scanf("%d %d", &m, &n);
    m--, n--;
    printf("%lld\n", comb(m + n, n));
    return 0;
}