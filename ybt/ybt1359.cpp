/**
* Number:ybt1359
* Title:围成面积
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
    if (mp[x][y] != 0)
        return;
    mp[x][y] = 1;
    for (int i = 0; i < 4; i++)
    {
        dfs(x + dir[i][0], y + dir[i][1]);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int ans = 0;
    memset(mp, -1, sizeof(mp));
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            scanf("%d", &mp[i][j]);
        }
    }
    for (int i = 1; i <= 10; i++)
    {
        dfs(1, i);
        dfs(10, i);
        dfs(i, 1);
        dfs(i, 10);
    }
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            if (mp[i][j] == 0)
                ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}