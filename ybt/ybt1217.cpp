/**
* Number:ybt1217
* Title: 棋盘问题
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

char buffer[128];
struct Point
{
    int x, y;
} pos[80];
int plen;
bool visp[80];
bool visx[16];
bool visy[16];
int ans;
int n, k;
void dfs(int pre, int dep)
{
    if (dep == k)
    {
        ans++;
        return;
    }
    for (int i = pre + 1; i < plen && dep + plen - i >= k; i++)
    {
        Point &p = pos[i];
        if (!visp[i] && !visx[p.x] && !visy[p.y])
        {
            visp[i] = true;
            visx[p.x] = true;
            visy[p.y] = true;
            dfs(i, dep + 1);
            visp[i] = false;
            visx[p.x] = false;
            visy[p.y] = false;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while (scanf("%d %d", &n, &k) != EOF && ~n && ~k)
    {
        plen = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%s", buffer);
            for (int j = 0; j < n; j++)
            {
                if (buffer[j] == '#')
                {
                    pos[plen].x = i;
                    pos[plen].y = j;
                    plen++;
                }
            }
        }
        ans = 0;
        dfs(-1, 0);
        printf("%d\n", ans);
    }
    return 0;
}