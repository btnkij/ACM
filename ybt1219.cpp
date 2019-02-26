/**
* Number:ybt1219
* Title:马走日
* Status:AC
* Tag:[bfs]
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

bool vis[16][16];
int n, m, tot;
int ans;
int dep = 1;
int dir[][2] = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
void dfs(int x, int y)
{
    if (dep == tot)
    {
        ans++;
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (0 <= xx && xx < n && 0 <= yy && yy < m && !vis[xx][yy])
        {
            vis[xx][yy] = true;
            dep++;
            dfs(xx, yy);
            dep--;
            vis[xx][yy] = false;
        }
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
        scanf("%d %d", &n, &m);
        int x, y;
        scanf("%d %d", &x, &y);
        ans = 0;
        vis[x][y] = true;
        tot = n * m;
        dfs(x, y);
        vis[x][y] = false;
        printf("%d\n", ans);
    }
    return 0;
}