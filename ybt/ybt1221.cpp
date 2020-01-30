/**
* Number:ybt1221
* Title:分成互质组
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

int gcd(int a, int b)
{
    while (b)
    {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}
int n, num[16];
int ans = INF;
int group[16][16], tot;
void dfs(int dep)
{
    if (dep == n)
    {
        ans = min(ans, tot);
        return;
    }
    int m = num[dep];
    for (int i = 0; i < tot; i++)
    {
        bool ok = true;
        for (int j = 1; j <= group[i][0]; j++)
        {
            if (gcd(m, group[i][j]) > 1)
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            group[i][0]++;
            group[i][group[i][0]] = m;
            dfs(dep + 1);
            group[i][0]--;
        }
    }
    group[tot][0] = 1;
    group[tot][1] = m;
    tot++;
    dfs(dep + 1);
    tot--;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", num + i);
    }
    dfs(0);
    printf("%d\n", ans);
    return 0;
}