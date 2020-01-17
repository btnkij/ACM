/**
* Number:hdu1078
* Title:FatMouse and Cheese
* Status:AC
* Tag:[记忆化搜索]
**/

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

int n,k;
int maze[110][110];
int dp[110][110];
const int dir[][2]={{-1,0},{1,0},{0,-1},{0,1}};
int dfs(int x,int y)
{
    if(~dp[x][y])return dp[x][y];
    int tmp=0;
    rep2(i,1,k,j,0,3)
    {
        int xx=x+i*dir[j][0], yy=y+i*dir[j][1];
        if(1<=xx && xx<=n && 1<=yy && yy<=n)
            if(maze[x][y]<maze[xx][yy])
                tmp=max(tmp,dfs(xx,yy));
    }
    return dp[x][y]=maze[x][y]+tmp;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n,k)!=EOF && ~n && ~k)
    {
        rep2(i,1,n,j,1,n)readi(maze[i][j]);
        clr(dp,-1);
        printf("%d\n",dfs(1,1));
    }
    return 0;
}