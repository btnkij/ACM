/**
* Number:ybt1215
* Title:迷宫
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
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(mp, '#', sizeof(mp));
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", &mp[i][1]);
        }
        int srcx, srcy, dstx, dsty;
        scanf("%d %d %d %d", &srcx, &srcy, &dstx, &dsty);
        srcx++, srcy++, dstx++, dsty++;
        queue<Node> Q;
        bool ans = false;
        Q.push((Node){srcx, srcy});
        while (!Q.empty())
        {
            Node node = Q.front();
            Q.pop();
            if (mp[node.x][node.y] != '.')
                continue;
            else if (node.x == dstx && node.y == dsty)
            {
                ans = true;
                break;
            }
            mp[node.x][node.y] = '#';
            for (int i = 0; i < 4; i++)
            {
                int xx = node.x + dir[i][0];
                int yy = node.y + dir[i][1];
                if (mp[xx][yy] == '.')
                    Q.push((Node){xx, yy});
            }
        }
        printf("%s\n", ans ? "YES" : "NO");
    }
    return 0;
}