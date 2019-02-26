/**
* Number:ybt1208
* Title:2的幂次方表示
* Status:AC
* Tag:[递归]
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

void solve(int n)
{
    bool first = true;
    for (int i = 14; i >= 0; i--)
    {
        if (n & (1 << i))
        {
            if (!first)
                putchar('+');
            first = false;
            if (i >= 3)
            {
                printf("2(");
                solve(i);
                printf(")");
            }
            else if (i == 2)
            {
                printf("2(2)");
            }
            else if (i == 1)
            {
                printf("2");
            }
            else if (i == 0)
            {
                printf("2(0)");
            }
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    solve(n);
    return 0;
}