/**
* Number:hdu1231
* Title:最大连续子序列
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
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

int arr[10010];
int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n)
    {
        int ans = -1, tmp = 0;
        int head = 0, tail = 0;
        int head1 = 0, tail1 = n - 1;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", arr + i);
            if (tmp + arr[i] >= 0)
            {
                tmp += arr[i];
                if (tmp > ans)
                {
                    tail1 = i;
                    head = head1;
                    tail = tail1;
                    ans = tmp;
                }
            }
            else
            {
                tmp = 0;
                head1 = i + 1;
            }
        }
        if (ans == -1)
            printf("0 %d %d\n", arr[0], arr[n - 1]);
        else
            printf("%d %d %d\n", ans, arr[head], arr[tail]);
    }
    return 0;
}