/**
* Number:ybt1202
* Title:Pell数列
* Status:AC
* Tag:[递推]
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

const int MAXN = 1e6 + 4;
int dp[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i < MAXN; i++)
    {
        dp[i] = ((dp[i - 1] << 1) + dp[i - 2]) % 32767;
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int a;
        scanf("%d", &a);
        printf("%d\n", dp[a]);
    }
    return 0;
}