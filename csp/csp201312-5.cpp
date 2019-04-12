/**
* Number:csp201312-5
* Title:I’m stuck!
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int dir[][2]={{-1,0},{0,1},{1,0},{0,-1}}; //up right down left
int r,c;
int sx, sy, tx, ty;
struct Node
{
    bool vis;
    bool to[4];
}nodes[60][60];
char maze[60][60];
struct Point
{
    int x,y;
};
bool stuck=true;
void bfs1()
{
    queue<Point> Q;
    Q.push((Point){sx,sy});
    nodes[sx][sy].vis=true;
    while(!Q.empty())
    {
        Point p=Q.front(); Q.pop();
        Node& u=nodes[p.x][p.y];
        if(maze[p.x][p.y]=='T')stuck=false;
        repne(i,0,4)
        {
            if(!u.to[i])continue;
            int x1=p.x+dir[i][0];
            int y1=p.y+dir[i][1];
            if(x1<0 || x1>=r || y1<0 || y1>=c
                || nodes[x1][y1].vis || maze[x1][y1]=='#')
                continue;
            Q.push((Point){x1,y1});
            nodes[x1][y1].vis=true;
        }
    }
}
void bfs2()
{
    queue<Point> Q;
    Q.push((Point){tx,ty});
    nodes[tx][ty].vis=false;
    while(!Q.empty())
    {
        Point p=Q.front(); Q.pop();
        Node& u=nodes[p.x][p.y];
        repne(i,0,4)
        {
            int x1=p.x+dir[i][0];
            int y1=p.y+dir[i][1];
            if(x1<0 || x1>=r || y1<0 || y1>=c
                || !nodes[x1][y1].vis || maze[x1][y1]=='#'
                || !nodes[x1][y1].to[(i+2)%4])
                continue;
            Q.push((Point){x1,y1});
            nodes[x1][y1].vis=false;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(r,c);
    repne(i,0,r)
    {
        reads(maze[i]);
        repne(j,0,c)
        {
            char ch=maze[i][j];
            bool* to=nodes[i][j].to;
            if(ch=='+')
                to[0]=to[1]=to[2]=to[3]=true;
            else if(ch=='-')
                to[1]=to[3]=true;
            else if(ch=='|')
                to[0]=to[2]=true;
            else if(ch=='.')
                to[2]=true;
            else if(ch=='S')
            {
                sx=i, sy=j;
                to[0]=to[1]=to[2]=to[3]=true;
            }
            else if(ch=='T')
            {
                tx=i, ty=j;
                to[0]=to[1]=to[2]=to[3]=true;
            }
        }
    }
    bfs1();
    if(stuck)
    {
        printf("I'm stuck!");
    }
    else
    {
        bfs2();
        int cnt=0;
        repne2(x,0,r,y,0,c)
            if(nodes[x][y].vis)
                cnt++;
        printf("%d",cnt);
    }
    return 0;
}