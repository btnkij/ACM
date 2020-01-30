/**
* Number:ybt1252
* Title:走迷宫
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
char maze[100][100];
int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
struct Node
{
    int x, y;
    int step;
};
int bfs()
{
    queue<Node> Q;
    Q.push((Node){0, 0, 1});
    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();
        if (node.x == h - 1 && node.y == l - 1)
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
    scanf("%d %d", &h, &l);
    for (int i = 0; i < h; i++)
    {
        scanf("%s", maze[i]);
    }
    int ans = bfs();
    printf("%d\n", ans);
    return 0;
}