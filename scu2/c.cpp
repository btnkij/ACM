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

int n,m,k,cnt;
char maze[110][110];
int dis[10][10];
struct Point
{
    int x,y;
}pos[10];
int dir[][2]={{-1,0},{1,0},{0,-1},{0,1}};
bool vis[110][110];
struct Node
{
    int x,y,step;
};
void bfs(int p)
{
    clr(vis,false);
    queue<Node> Q;
    Q.push((Node){pos[p].x,pos[p].y,0});
    vis[pos[p].x][pos[p].y]=true;
    while(!Q.empty())
    {
        Node cur=Q.front(); Q.pop();
        int ch=maze[cur.x][cur.y];
        if('0'<=ch && ch<='9')
        {
            dis[p][ch&0xF]=cur.step;
        }
        for(int i=0;i<4;i++)
        {
            int nxtx=cur.x+dir[i][0], nxty=cur.y+dir[i][1];
            if(maze[nxtx][nxty]=='#' || vis[nxtx][nxty])continue;
            vis[nxtx][nxty]=true;
            Node nxt=(Node){nxtx,nxty,cur.step+1};
            Q.push(nxt);
        }
    }
}
bool vis2[10];
int ans;
void dfs(int p, int sum, int dep)
{
    if(dep==cnt)
    {
        ans=min(ans,sum);
        return;
    }
    vis2[p]=true;
    for(int i=0;i<=n;i++)
    {
        if(vis2[i])continue;
        dfs(i,sum+dis[p][i],dep+1);
    }
    vis2[p]=false;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n,m)!=EOF && n && m)
    {
        clr(maze,'#');
        clr(dis,INF);
        rep(i,1,n)
        {
            reads(&maze[i][1]);
            rep(j,1,m)
            {
                if(maze[i][j]=='@')
                {
                    pos[0].x=i, pos[0].y=j;
                    maze[i][j]='0';
                }
            }
            maze[i][m+1]='#';
        }
        readi(k);
        bool flag=false;
        cnt=0;
        rep(i,1,k)
        {
            readi(pos[i].x, pos[i].y);
            if(maze[pos[i].x][pos[i].y]!='.')continue;
            maze[pos[i].x][pos[i].y]=0x30|++cnt;
        }
        if(flag)
        {
            printf("-1\n");
            continue;
        }
        for(int i=0;i<=cnt;i++)
        {
            bfs(i);
            for(int j=0;j<=cnt;j++)
            {
                if(!vis[pos[j].x][pos[j].y])
                {
                    flag=true;
                    break;
                }
            }
        }
        if(flag)
        {
            printf("-1\n");
            continue;
        }
        ans=INF;
        dfs(0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}