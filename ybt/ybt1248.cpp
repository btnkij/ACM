/**
* Number:ybt1248
* Title:Dungeon Master
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

int h, l, w;
char maze[100][100][100];
int dir[][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
struct Node
{
    int x, y, z;
    int step;
};
int bfs(int x, int y, int z)
{
    queue<Node> Q;
    Q.push((Node){x, y, z, 0});
    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();
        if (maze[node.x][node.y][node.z] == 'E')
            return node.step;
        if (maze[node.x][node.y][node.z] != '.')
            continue;
        maze[node.x][node.y][node.z] = '#';
        for (int i = 0; i < 6; i++)
        {
            int xx = node.x + dir[i][0];
            int yy = node.y + dir[i][1];
            int zz = node.z + dir[i][2];
            if (0 <= xx && xx < h && 0 <= yy && yy < l && 0 <= zz && zz < w && maze[xx][yy][zz] != '#')
            {
                Q.push((Node){xx, yy, zz, node.step + 1});
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
    while (scanf("%d %d %d", &h, &l, &w) != EOF && h && l && w)
    {
        int srcx, srcy, srcz;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < l; j++)
            {
                scanf("%s", &maze[i][j]);
                for (int k = 0; k < w; k++)
                {
                    if (maze[i][j][k] == 'S')
                    {
                        maze[i][j][k] = '.';
                        srcx = i, srcy = j, srcz = k;
                        break;
                    }
                }
            }
        }
        int ans = bfs(srcx, srcy, srcz);
        if (ans == INF)
        {
            printf("Trapped!\n");
        }
        else
        {
            printf("Escaped in %d minute(s).\n", ans);
        }
    }
    return 0;
}