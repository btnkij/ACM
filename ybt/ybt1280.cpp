/**
* Number:ybt1280
* Title:滑雪
* Status:AC
* Tag:[记忆化搜索]
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

int nrow,ncol;
int maze[104][104];
bool vis[104][104];
int dp[104][104];
int dir[][2]={{0,1},{0,-1},{1,0},{-1,0}};
int dfs(int x,int y)
{
    if(vis[x][y])return dp[x][y];
    vis[x][y]=true;
    int &ans=dp[x][y];
    repne(i,0,4)
    {
        int xx=x+dir[i][0];
        int yy=y+dir[i][1];
        if(0<=xx && xx<nrow && 0<=yy && yy<ncol && maze[x][y]>maze[xx][yy])
            ans=max(ans,dfs(xx,yy));
    }
    ans++;
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(nrow,ncol);
    repne2(i,0,nrow,j,0,ncol)readi(maze[i][j]);
    int ans=0;
    repne2(i,0,nrow,j,0,ncol)ans=max(ans,dfs(i,j));
    printf("%d\n",ans);
    return 0;
}