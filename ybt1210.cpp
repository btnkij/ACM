/**
* Number:ybt1210
* Title:因子分解
* Status:AC
* Tag:[基础]
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

int factor[104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        while (n % i == 0)
        {
            n /= i;
            factor[i]++;
        }
    }
    bool first = true;
    for (int i = 2; i < 100; i++)
    {
        if (!factor[i])
            continue;
        if (!first)
            putchar('*');
        first = false;
        if (factor[i] >= 2)
        {
            printf("%d^%d", i, factor[i]);
        }
        else if (factor[i] == 1)
        {
            printf("%d", i);
        }
    }
    return 0;
}