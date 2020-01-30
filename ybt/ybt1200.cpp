/**
* Number:ybt1200
* Title:分解因数
* Status:AC
* Tag:[dfs]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int ans;
void dfs(int n, int pre)
{
    if (n == 1)
    {
        ans++;
        return;
    }
    for (int i = pre; i <= n; i++)
    {
        if (n % i == 0)
            dfs(n / i, i);
    }
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        ans = 0;
        dfs(n, 2);
        printf("%d\n", ans);
    }
    return 0;
}