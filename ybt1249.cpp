/**
* Number:ybt1249
* Title:Lake Counting
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

char maze[120][120];
int dir[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
void dfs(int x, int y)
{
    maze[x][y] = '.';
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (maze[xx][yy] == 'W')
        {
            dfs(xx, yy);
        }
    }
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
        scanf("%s", &maze[i][1]);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (maze[i][j] == 'W')
            {
                ans++;
                dfs(i, j);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}