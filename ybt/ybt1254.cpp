/**
* Number:ybt1254
* Title:走出迷宫
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

int h, l;
char maze[104][104];
int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
struct Node
{
    int x, y;
    int step;
};
int bfs(int x, int y)
{
    queue<Node> Q;
    Q.push((Node){x, y, 0});
    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();
        if (maze[node.x][node.y] == 'T')
            return node.step;
        if (maze[node.x][node.y] != '.')
            continue;
        maze[node.x][node.y] = '#';
        for (int i = 0; i < 4; i++)
        {
            int xx = node.x + dir[i][0];
            int yy = node.y + dir[i][1];
            if (0 <= xx && xx < h && 0 <= yy && yy < l && maze[xx][yy] != '#')
            {
                Q.push((Node){xx, yy, node.step + 1});
            }
        }
    }
    return INF;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while (scanf("%d %d", &h, &l) != EOF && h && l)
    {
        int srcx, srcy;
        for (int i = 0; i < h; i++)
        {
            scanf("%s", maze[i]);
            for (int k = 0; k < l; k++)
            {
                if (maze[i][k] == 'S')
                {
                    maze[i][k] = '.';
                    srcx = i, srcy = k;
                    break;
                }
            }
        }
        int ans = bfs(srcx, srcy);
        printf("%d\n", ans);
    }
    return 0;
}