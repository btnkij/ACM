#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const double eps=1e-6;
struct Vector
{
    double x,y;
};
int side(const Vector& lhs, const Vector& rhs)
{
    double cross = lhs.x * rhs.y - lhs.y * rhs.x;
    if(fabs(cross)<eps)return 0;
    return cross<0?-1:1;
}
char maze[24][24];
struct Node
{
    int x,y,step;
    bool operator<(const Node& rhs)const
    {
        return step>rhs.step;
    }
};
const int dir[][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
bool vis[24][24];
int dijkstra(int n,int sx,int sy,int dx,int dy)
{
    priority_queue<Node> Q;
    Q.push((Node){sx,sy,0});
    clr(vis,false);
    while(!Q.empty())
    {
        Node cur=Q.top(); Q.pop();
        if(cur.x==dx && cur.y==dy)return cur.step;
        vis[cur.x][cur.y]=true;
        repne(i,0,8)
        {
            Node nxt=(Node){cur.x+dir[i][0],cur.y+dir[i][1],cur.step+1};
            if(nxt.x<0 || nxt.x>=n || nxt.y<0 || nxt.y>=n)continue;
            if(maze[nxt.x][nxt.y]!='.' || vis[nxt.x][nxt.y])continue;
            Q.push(nxt);
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
    int n;
    while(readi(n)!=EOF)
    {
        double x[4],y[4];
        repne(i,0,3)scanf("%lf %lf",x+i,y+i);
        clr(maze,0);
        repne(i,0,n)scanf("%s",maze[i]);
        Vector e0=(Vector){x[1]-x[0],y[1]-y[0]};
        Vector e1=(Vector){x[2]-x[1],y[2]-y[1]};
        Vector e2=(Vector){x[0]-x[2],y[0]-y[2]};
        int inner0=side(e0,(Vector){x[2]-x[0],y[2]-y[0]});
        int inner1=side(e1,(Vector){x[0]-x[1],y[0]-y[1]});
        int inner2=side(e2,(Vector){x[1]-x[2],y[1]-y[2]});
        if(!(inner0==0 || inner1==0 || inner2==0))
        {
            repne2(i,0,n,j,0,n)
            {
                if(side(e0,(Vector){j-x[0],(n-1-i)-y[0]})==inner0
                && side(e1,(Vector){j-x[1],(n-1-i)-y[1]})==inner1
                && side(e2,(Vector){j-x[2],(n-1-i)-y[2]})==inner2)
                {
                    maze[i][j]='#';
                }
            }
        }
        int ans=dijkstra(n,n-1,0,0,n-1);
        printf("%d\n",ans);
    }
    return 0;
}