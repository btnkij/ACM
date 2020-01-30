/**
* Number:ybt1335
* Title:连通块
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

int mp[110][110];
int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
void dfs(int x, int y)
{
    if (mp[x][y] == 0)
        return;
    mp[x][y] = 0;
    for (int i = 0; i < 4; i++)
        dfs(x + dir[i][0], y + dir[i][1]);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &mp[i][j]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] == 1)
            {
                dfs(i, j);
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}