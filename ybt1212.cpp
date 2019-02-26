/**
* Number:ybt1212
* Title:LETTERS
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

int dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
char mp[24][24];
bool path[24][24];
bool vis[256];
int ans;
void dfs(int x, int y, int dep)
{
    path[x][y] = vis[mp[x][y]] = true;
    ans = max(ans, dep);
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        int ch = mp[xx][yy] & 0xFF;
        if (ch && !vis[ch] && !path[xx][yy])
        {
            dfs(xx, yy, dep + 1);
        }
    }
    path[x][y] = vis[mp[x][y]] = false;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n_row, n_col;
    scanf("%d %d", &n_row, &n_col);
    for (int i = 1; i <= n_row; i++)
    {
        scanf("%s", &mp[i][1]);
    }
    dfs(1, 1, 1);
    printf("%d\n", ans);
    return 0;
}