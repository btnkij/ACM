/**
* Number:loj6223
* Title:「网络流 24 题」汽车加油行驶问题
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

int n,k,a,b,c;
int maze[104][104];
int vis[104][104][14];
int dir[][2]={{-1,0},{0,-1},{1,0},{0,1}};
struct Node
{
    int x,y,d,cost;
    bool operator<(const Node& rhs)const
    {
        return cost>rhs.cost;
    }
};
int dijkstra()
{
    priority_queue<Node> P;
    P.push((Node){1,1,k,0});
    while(!P.empty())
    {
        Node u=P.top(); P.pop();
        if(vis[u.x][u.y][u.d])continue;
        if(u.x==n && u.y==n)return u.cost;
        vis[u.x][u.y][u.d]=true;
        if(u.d>0)
        {
            repne(i,0,4)
            {
                int nx=u.x+dir[i][0], ny=u.y+dir[i][1];
                if(nx<1 || nx>n || ny<1 || ny>n)continue;
                int nd=maze[nx][ny] ? k : u.d-1;
                if(vis[nx][ny][nd])continue;
                int nc=u.cost;
                if(maze[nx][ny])nc+=a;
                if(i<2)nc+=b;
                P.push((Node){nx,ny,nd,nc});
            }
        }
        if(!vis[u.x][u.y][k])
            P.push((Node){u.x, u.y, k, u.cost+a+c});
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(n,k);
    readi3(a,b,c);
    rep2(i,1,n,j,1,n)readi(maze[i][j]);
    int ans=dijkstra();
    printf("%d",ans);
    return 0;
}