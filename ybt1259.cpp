/**
* Number:ybt1259
* Title:求最长不下降序列
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

int num[210];
int dp[210], pre[210];
void print(int i)
{
    if (~pre[i])
        print(pre[i]);
    if (~pre[i])
        putchar(' ');
    printf("%d", num[i]);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    int ans1 = 0, ans2;
    for (int i = 0; i < n; i++)
    {
        readi(num[i]);
        int tmp = 0, p = -1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (num[i] >= num[j] && dp[j] > tmp)
            {
                tmp = dp[j];
                p = j;
            }
        }
        dp[i] = tmp + 1;
        pre[i] = p;
        if (dp[i] > ans1)
        {
            ans1 = dp[i];
            ans2 = i;
        }
    }
    printf("max=%d\n", ans1);
    print(ans2);
    return 0;
}