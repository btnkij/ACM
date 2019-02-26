/**
* Number:ybt1206
* Title:放苹果
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

int M, N, ans;
void dfs(int m, int pre, int dep)
{
    if (m == 0 || dep == N)
    {
        ans++;
        return;
    }
    for (int i = min(m, pre); i >= 0 && (N - dep) * i >= m; i--)
    {
        dfs(m - i, i, dep + 1);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &M, &N);
        ans = 0;
        dfs(M, M, 0);
        printf("%d\n", ans);
    }
    return 0;
}