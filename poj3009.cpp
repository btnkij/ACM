/**
* Number:poj3009
* Title:Curling 2.0
* Status:AC
* Tag:[dfs]
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
int maze[40][40];
int dfs(int x,int y,int dep)
{
    if(dep>10)
    {
        return INF;
    }
    int ans=INF;
    for(int i=0;i<4;i++)
    {
        int x1=x+dir[i][0], y1=y+dir[i][1];
        if(maze[x1][y1]==1)continue;
        while(maze[x1][y1]==0)
        {
            x1+=dir[i][0];
            y1+=dir[i][1];
        }
        switch(maze[x1][y1])
        {
        case -1:
            continue;
        case 1:
            maze[x1][y1]=0;
            ans=min(ans,dfs(x1-dir[i][0],y1-dir[i][1],dep+1));
            maze[x1][y1]=1;
            break;
        case 3:
            ans=min(ans,dep);
            break;
        }
    }
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int h,w;
    while(scanf("%d %d",&w,&h)!=EOF && (w|h))
    {
        memset(maze,-1,sizeof(maze));
        int sx,sy;
        for(int i=1;i<=h;i++)
        {
            for(int j=1;j<=w;j++)
            {
                scanf("%d",&maze[i][j]);
                if(maze[i][j]==2)
                {
                    sx=i, sy=j;
                    maze[i][j]=0;
                }
            }
        }
        int ans=dfs(sx,sy,1);
        printf("%d\n",ans==INF ? -1 : ans);
    }
    return 0;
}