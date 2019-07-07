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
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

char maze[40][40];
ll dp[40][40][2];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)reads(maze[i]+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(maze[i][j]=='B')
            {
                maze[i][j]='.';
                for(int x=i;x>=1;x--)
                {
                    for(int y=j;y>=1;y--)
                    {
                        if(maze[x][y]=='.')maze[x][y]='B';
                        else if(maze[x][y]=='B')break;
                        else if(maze[x][y]=='R')
                        {
                            printf("0");
                            return 0;
                        }
                    }
                }
            }
        }
    }
    for(int i=n;i>=1;i--)
    {
        for(int j=m;j>=1;j--)
        {
            if(maze[i][j]=='R')
            {
                maze[i][j]='.';
                for(int x=i;x<=n;x++)
                {
                    for(int y=j;y<=m;y++)
                    {
                        if(maze[x][y]=='.')maze[x][y]='R';
                        else if(maze[x][y]=='R')break;
                        else if(maze[x][y]=='B')
                        {
                            printf("0");
                            return 0;
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<40;i++)dp[0][i][0]=dp[i][0][0]=1;
    for(int x=1;x<=n;x++)
    {
        for(int y=1;y<=m;y++)
        {
            ll *left=dp[x][y-1], *up=dp[x-1][y];
            if(maze[x][y]=='B')
            {
                dp[x][y][0]=left[0]*up[0];
            }
            else if(maze[x][y]=='R')
            {
                dp[x][y][1]=(left[0]+up[0])*(left[1]+up[1]);
            }
            else
            {
                dp[x][y][0]=left[0]*up[0];
                dp[x][y][1]=(left[0]+up[0])*(left[1]+up[1]);
            }
        }
    }
    printf("%lld",dp[n][m][0]+dp[n][m][1]);
    return 0;
}