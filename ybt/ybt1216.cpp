/**
* Number:ybt1216
* Title:红与黑
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

struct Node
{
    int x, y;
};
int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char mp[104][104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int ncol, nrow;
    while (scanf("%d %d", &ncol, &nrow) != EOF && ncol && nrow)
    {
        memset(mp, '#', sizeof(mp));
        int srcx, srcy;
        for (int i = 1; i <= nrow; i++)
        {
            scanf("%s", &mp[i][1]);
            for (int j = 1; j <= ncol; j++)
            {
                if (mp[i][j] == '@')
                {
                    srcx = i;
                    srcy = j;
                    mp[i][j] = '.';
                    break;
                }
            }
        }
        queue<Node> Q;
        Q.push((Node){srcx, srcy});
        int ans = 0;
        while (!Q.empty())
        {
            Node node = Q.front();
            Q.pop();
            if (mp[node.x][node.y] == '.')
                ans++;
            else
                continue;
            mp[node.x][node.y] = '#';
            for (int i = 0; i < 4; i++)
            {
                int xx = node.x + dir[i][0];
                int yy = node.y + dir[i][1];
                if (mp[xx][yy] == '.')
                    Q.push((Node){xx, yy});
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}