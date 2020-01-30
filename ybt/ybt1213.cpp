/**
* Number:ybt1213
* Title:八皇后问题
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

int kase = 1;
int mp[8][8];
bool ok(int x, int y)
{
    int xx = x - 1, yy = y - 1;
    while (xx >= 0 && yy >= 0)
    {
        if (mp[xx][yy] == 1)
            return false;
        xx--, yy--;
    }
    xx = x + 1, yy = y - 1;
    while (xx < 8 && yy >= 0)
    {
        if (mp[xx][yy] == 1)
            return false;
        xx++, yy--;
    }
    xx = x, yy = y - 1;
    while (yy >= 0)
    {
        if (mp[xx][yy] == 1)
            return false;
        yy--;
    }
    return true;
}
void dfs(int dep)
{
    if (dep == 8)
    {
        printf("No. %d\n", kase++);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                printf("%d ", mp[i][j]);
            }
            putchar('\n');
        }
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        if (ok(i, dep))
        {
            mp[i][dep] = 1;
            dfs(dep + 1);
            mp[i][dep] = 0;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    dfs(0);
    return 0;
}