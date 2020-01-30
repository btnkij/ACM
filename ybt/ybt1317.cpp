/**
* Number:ybt1317
* Title:组合的输出
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

int n, r;
int ans[30];
void dfs(int pre, int dep)
{
    if (dep == r)
    {
        for (int i = 0; i < r; i++)
        {
            printf("%3d", ans[i]);
        }
        putchar('\n');
        return;
    }
    for (int i = pre + 1; i <= n && n - i + 1 + dep >= r; i++)
    {
        ans[dep] = i;
        dfs(i, dep + 1);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d %d", &n, &r);
    dfs(0, 0);
    return 0;
}