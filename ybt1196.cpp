/**
* Number:ybt1196
* Title:踩方格
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

int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}};
bool vis[50][50];
int dfs(int x, int y, int dep)
{
    if (dep == 0)
        return 1;
    vis[x][y] = true;
    int ans = 0;
    for (int i = 0; i < 3; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (vis[xx][yy])
            continue;
        ans += dfs(xx, yy, dep - 1);
    }
    vis[x][y] = false;
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    printf("%d\n", dfs(25, 0, n));
    return 0;
}