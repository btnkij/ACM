/**
* Number:ybt1255
* Title:迷宫问题
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

const int h = 5, l = 5;
int maze[8][8];
int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int path[8][8];
struct Node
{
    int x, y;
    int dirct;
};
void bfs()
{
    queue<Node> Q;
    Q.push((Node){0, 0, -1});
    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();
        if (maze[node.x][node.y] != 0)
            continue;
        maze[node.x][node.y] = 1;
        path[node.x][node.y] = node.dirct;
        if (node.x == h - 1 && node.y == l - 1)
            return;
        for (int i = 0; i < 4; i++)
        {
            int xx = node.x + dir[i][0];
            int yy = node.y + dir[i][1];
            if (0 <= xx && xx < h && 0 <= yy && yy < l && maze[xx][yy] != 1)
            {
                Q.push((Node){xx, yy, i});
            }
        }
    }
    return;
}
void print(int x, int y)
{
    if (~path[x][y])
    {
        int i = path[x][y];
        print(x - dir[i][0], y - dir[i][1]);
    }
    printf("(%d, %d)\n", x, y);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < l; j++)
        {
            scanf("%d", &maze[i][j]);
        }
    }
    bfs();
    print(h - 1, l - 1);
    return 0;
}