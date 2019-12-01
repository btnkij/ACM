/**
* Number:poj1562
* Title:Oil Deposits 
* Status:AC
* Tag:[dfs/bfs]
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

// 定义8个方向向量
int dir[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
char maze[110][110]; // 地图

void dfs(int x, int y)
{
    if(maze[x][y] != '@')return;
    maze[x][y] = '*'; // 如果是@, 消去
    repne(i,0,8)dfs(x + dir[i][0], y + dir[i][1]); // 向8个方向搜索
}

typedef pair<int, int> Point;
void bfs(int x, int y)
{
    queue<Point> Q;
    Q.push(Point(x, y));
    while(!Q.empty())
    {
        Point p = Q.front(); Q.pop();
        if(maze[p.first][p.second] != '@')continue;
        maze[p.first][p.second] = '*';
        repne(i,0,8)
        {
            int x1 = p.first + dir[i][0];
            int y1 = p.second + dir[i][1];
            if(maze[x1][y1] == '@')
                Q.push(Point(x1, y1));
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m, n;
    while(readi(m, n) != EOF && m && n)
    {
        mset(maze, 0);
        rep(i,1,m)reads(maze[i] + 1);
        int ans = 0;
        rep2(x,1,m,y,1,n)
        {
            if(maze[x][y] == '@') // 如果是@
            {
                ans++; // 答案+1
                dfs(x, y); // 将与(x, y)连通的@消去
                //bfs(x, y); // bfs同样可以
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}