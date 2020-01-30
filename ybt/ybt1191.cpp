/**
* Number:ybt1191
* Title:流感传染
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

struct Point
{
    int x, y;
    int t;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
        t = 1;
    }
};

int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char mp[104][104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    queue<Point> Q;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", mp[i] + 1);
        for (int j = 1; j <= n; j++)
        {
            if (mp[i][j] == '@')
            {
                Q.push(Point(i, j));
            }
        }
    }
    int m;
    scanf("%d", &m);
    int ans = 0;
    while (!Q.empty())
    {
        Point node = Q.front();
        Q.pop();
        ans++;
        if (node.t < m)
        {
            for (int i = 0; i < 4; i++)
            {
                int x = node.x + dir[i][0];
                int y = node.y + dir[i][1];
                if (mp[x][y] == '.')
                {
                    Point p(x, y);
                    p.t = node.t + 1;
                    Q.push(p);
                    mp[x][y] = 'x';
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}