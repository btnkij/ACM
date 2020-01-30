/**
* Number:ybt1250
* Title:The Castle
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

int nrow, ncol;
int maze[60][60];
int cnt;
void dfs(int x, int y)
{
    if (maze[x][y] == -1)
        return;
    int t = maze[x][y];
    maze[x][y] = -1;
    cnt++;
    if ((t & 1) == 0 && y >= 1)
        dfs(x, y - 1);
    if ((t & 2) == 0 && x >= 1)
        dfs(x - 1, y);
    if ((t & 4) == 0 && y < ncol - 1)
        dfs(x, y + 1);
    if ((t & 8) == 0 && x < nrow - 1)
        dfs(x + 1, y);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d %d", &nrow, &ncol);
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            scanf("%d", &maze[i][j]);
        }
    }
    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            if (~maze[i][j])
            {
                ans1++;
                cnt = 0;
                dfs(i, j);
                ans2 = max(ans2, cnt);
            }
        }
    }
    printf("%d\n%d\n", ans1, ans2);
    return 0;
}