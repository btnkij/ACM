/**
* Number:ybt1257
* Title:Knight Moves
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
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))

bool vis[304][304];
struct Node
{
    int x, y;
    int step;
};
int dir[][2] = {{1, 2}, {-1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, 1}, {-2, -1}};
int L;
int bfs(int srcx, int srcy, int dstx, int dsty)
{
    mset(vis, false);
    queue<Node> Q;
    Q.push((Node){srcx, srcy, 0});
    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();
        if (vis[node.x][node.y])
            continue;
        if (node.x == dstx && node.y == dsty)
            return node.step;
        vis[node.x][node.y] = true;
        for (int i = 0; i < 8; i++)
        {
            int xx = node.x + dir[i][0];
            int yy = node.y + dir[i][1];
            if (0 <= xx && xx < L && 0 <= yy && yy < L && !vis[xx][yy])
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
        readi(L);
        int srcx, srcy, dstx, dsty;
        readi4(srcx, srcy, dstx, dsty);
        int ans = bfs(srcx, srcy, dstx, dsty);
        printf("%d\n", ans);
    }
    return 0;
}