/**
* Number:aizu0558
* Title:Cheese
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

const int dir[][2]={{-1,0},{1,0},{0,-1},{0,1}};
int sx[20],sy[20];
char maze[1010][1010];
bool vis[1010][1010];
struct Node
{
    int x,y,cost;
};
int bfs(int srcx,int srcy,int dstx,int dsty)
{
    memset(vis,0,sizeof(vis));
    queue<Node> Q;
    Q.push({srcx,srcy,0});
    vis[srcx][srcy]=true;
    while(!Q.empty())
    {
        Node cur=Q.front();
        Q.pop();
        if(cur.x==dstx && cur.y==dsty)
        {
            return cur.cost;
        }
        for(int i=0;i<4;i++)
        {
            Node nxt={cur.x+dir[i][0], cur.y+dir[i][1], cur.cost+1};
            if(maze[nxt.x][nxt.y]=='.' && !vis[nxt.x][nxt.y])
            {
                Q.push(nxt);
                vis[nxt.x][nxt.y]=true;
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
    ios::sync_with_stdio(false); cin.tie(0);
    int h,w,n;
    cin>>h>>w>>n;
    for(int i=1;i<=h;i++)
    {
        cin>>maze[i]+1;
        for(int j=1;j<=w;j++)
        {
            if(maze[i][j]=='S')
            {
                sx[0]=i, sy[0]=j;
                maze[i][j]='.';
            }
            else if('1'<=maze[i][j] && maze[i][j]<='9')
            {
                sx[maze[i][j]&0xF]=i, sy[maze[i][j]&0xF]=j;
                maze[i][j]='.';
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=bfs(sx[i-1],sy[i-1],sx[i],sy[i]);
    }
    printf("%d\n",ans);
    return 0;
}