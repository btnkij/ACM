/**
* Number:ybt1318
* Title:自然数的拆分
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

int N;
int num[1000], tot;
void dfs(int n, int pre)
{
    if (n == 0)
    {
        printf("%d=%d", N, num[0]);
        for (int i = 1; i < tot; i++)
        {
            printf("+%d", num[i]);
        }
        putchar('\n');
        return;
    }
    if (n < pre)
        return;
    for (int i = pre; i <= n && i < N; i++)
    {
        num[tot++] = i;
        dfs(n - i, i);
        tot--;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d", &N);
    dfs(N, 1);
    return 0;
}