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

const int MAXN=2010;
const int MOD=1e9+7;
char maze[MAXN][MAXN];
int nroom[MAXN][MAXN][2];
int pre[MAXN][MAXN][2];
int dp[MAXN][MAXN][2];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)reads(maze[i]+1);
    if(n==1 && m==1)
    {
        printf("%d",maze[1][1]=='.'?1:0);
        return 0;
    }
    dp[n][m][0]=dp[n][m][1]=pre[n][m][0]=pre[n][m][1]=1;
    for(int i=n;i>=1;i--)
    {
        for(int j=m;j>=1;j--)
        {
            if(!(i==n && j==m))
            {
                dp[i][j][0]=((pre[i][j+1][1]-pre[i][j+nroom[i][j+1][0]+1][1])%MOD+MOD)%MOD;
                dp[i][j][1]=((pre[i+1][j][0]-pre[i+nroom[i+1][j][1]+1][j][0])%MOD+MOD)%MOD;
            }
            pre[i][j][0]=(pre[i+1][j][0]+dp[i][j][0])%MOD;
            pre[i][j][1]=(pre[i][j+1][1]+dp[i][j][1])%MOD;
            nroom[i][j][0]=nroom[i][j+1][0]+int(maze[i][j]=='.');
            nroom[i][j][1]=nroom[i+1][j][1]+int(maze[i][j]=='.');
        }
    }
    // rep(i,1,n)
    // {
    //     rep(j,1,m)printf("(%d, %d) ",dp[i][j][0],dp[i][j][1]);
    //     puts("");
    // }
    printf("%d",(dp[1][1][0]+dp[1][1][1])%MOD);
    return 0;
}