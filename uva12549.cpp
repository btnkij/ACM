/**
* Number:uva12549
* Title:Sentry Robots
* Status:AC
* Tag:[二分图, hungary, 最小点覆盖]
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

struct Edge
{
    int from,to,nxt;
}edges[2510*2510];
int head[2510],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int match[2510];
bool vis[2510];
int dfs(int u)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(vis[v])continue;
        vis[v]=true;
        if(!match[v] || dfs(match[v]))
        {
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
int maxmatch(int nx)
{
    int ans=0;
    clr(match,0);
    rep(i,1,nx)
    {
        clr(vis,false);
        ans+=dfs(i);
    }
    return ans;
}

char maze[110][110];
pair<int,int> pos[110][110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int r,c; readi(r,c);
        int p; readi(p);
        clr(maze,0);
        repne(i,0,p)
        {
            int x,y; readi(x,y);
            maze[x][y]='*';
        }
        int w; readi(w);
        repne(i,0,w)
        {
            int x,y; readi(x,y);
            maze[x][y]='#';
        }
        int nx=0,ny=0;
        rep(i,1,r)
        {
            bool flag=true;
            rep(j,1,c)
            {
                if(maze[i][j]=='*')
                {
                    if(flag)nx++;
                    pos[i][j].first=nx;
                    flag=false;
                }
                else if(maze[i][j]=='#')flag=true;
            }
        }
        rep(j,1,c)
        {
            bool flag=true;
            rep(i,1,r)
            {
                if(maze[i][j]=='*')
                {
                    if(flag)ny++;
                    pos[i][j].second=ny;
                    flag=false;
                }
                else if(maze[i][j]=='#')flag=true;
            }
        }
        clr(head,-1); edgeid=0;
        rep2(i,1,r,j,1,c)
        {
            if(maze[i][j]=='*')
            {
                addedge(pos[i][j].first,pos[i][j].second);
            }
        }
        printf("%d\n",maxmatch(nx));
    }
    return 0;
}