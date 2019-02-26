/**
* Number:ybt1333
* Title:Blah数集
* Status:AC
* Tag:[优先队列]
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

ll arr[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while (scanf("%lld %d", &arr[1], &n) != EOF)
    {
        ll *head2 = &arr[1], *head3 = &arr[1];
        for (int i = 2; i <= n; i++)
        {
            ll a = (*head2) * 2 + 1;
            ll b = (*head3) * 3 + 1;
            if (a < b)
            {
                arr[i] = a;
                head2++;
            }
            else if (a > b)
            {
                arr[i] = b;
                head3++;
            }
            else
            {
                arr[i] = a;
                head2++;
                head3++;
            }
        }
        printf("%lld\n", arr[n]);
    }
    return 0;
}