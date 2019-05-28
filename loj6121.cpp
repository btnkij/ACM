/**
* Number:loj6121
* Title:孤岛营救问题
* Status:AC
* Tag:[dijkstra]
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

int dir[][2]={{-1,0},{1,0},{0,-1},{0,1}};
struct Cell
{
    int key,gate[4];
    bool wall[4];
}maze[14][14];
struct Node
{
    int x,y,key;
    int step;
    bool operator<(const Node& rhs)const
    {
        return step>rhs.step;
    }
};
int n,m;
bool vis[14][14][1<<15];
int dijkstra()
{
    priority_queue<Node> P;
    P.push((Node){1,1,0,0});
    while(!P.empty())
    {
        Node u=P.top(); P.pop();
        if(vis[u.x][u.y][u.key])continue;
        if(u.x==n && u.y==m)return u.step;
        vis[u.x][u.y][u.key]=true;
        repne(i,0,4)
        {
            Cell& c=maze[u.x][u.y];
            if(c.wall[i] || c.gate[i] && (1<<c.gate[i]&u.key)==0)continue;
            int nxtx=u.x+dir[i][0], nxty=u.y+dir[i][1];
            if(nxtx<1 || nxtx>n || nxty<1 || nxty>m)continue;
            int nxtk=u.key|maze[nxtx][nxty].key;
            if(vis[nxtx][nxty][nxtk])continue;
            P.push((Node){nxtx,nxty,nxtk,u.step+1});
        }
    }
    return -1;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int p;
    readi3(n,m,p);
    int k; readi(k);
    while(k--)
    {
        int x1,y1,x2,y2,g;
        readi4(x1,y1,x2,y2); readi(g);
        repne(i,0,4)
        {
            if(x1+dir[i][0]==x2 && y1+dir[i][1]==y2)
            {
                if(g>0)maze[x1][y1].gate[i]=g, maze[x2][y2].gate[i^1]=g;
                else maze[x1][y1].wall[i]=maze[x2][y2].wall[i^1]=true;
                break;
            }
        }
    }
    int s; readi(s);
    while(s--)
    {
        int x,y,q;
        readi3(x,y,q);
        maze[x][y].key|=(1<<q);
    }
    int ans=dijkstra();
    printf("%d",ans);
    return 0;
}