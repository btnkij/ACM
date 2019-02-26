/**
* Number:ybt1329
* Title:细胞
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

int n, m;
int mp[100][100];
int dir[][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
void dfs(int x, int y)
{
    mp[x][y] = 0;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (mp[xx][yy])
            dfs(xx, yy);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%1d", &mp[i][j]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j])
            {
                ans++;
                dfs(i, j);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}