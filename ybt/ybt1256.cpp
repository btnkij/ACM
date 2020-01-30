/**
* Number:ybt1256
* Title:献给阿尔吉侬的花束
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)

int nrow, ncol;
char maze[204][204];
int dir[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
struct Node
{
    int x, y;
    int step;
};
int bfs(int srcx, int srcy)
{
    queue<Node> Q;
    Q.push((Node){srcx, srcy, 0});
    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();
        if (maze[node.x][node.y] == 'E')
            return node.step;
        if (maze[node.x][node.y] != '.')
            continue;
        maze[node.x][node.y] = '#';
        for (int i = 0; i < 4; i++)
        {
            int xx = node.x + dir[i][0];
            int yy = node.y + dir[i][1];
            if (0 <= xx && xx < nrow && 0 <= yy && yy < ncol && maze[xx][yy] != '#')
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
    int T;
    readi(T);
    while (T--)
    {
        readi2(nrow, ncol);
        int srcx, srcy;
        for (int i = 0; i < nrow; i++)
        {
            scanf("%s", maze[i]);
            for (int j = 0; j < ncol; j++)
            {
                if (maze[i][j] == 'S')
                {
                    srcx = i, srcy = j;
                    maze[i][j] = '.';
                    break;
                }
            }
        }
        int ans = bfs(srcx, srcy);
        if (ans == INF)
            printf("oop!\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}