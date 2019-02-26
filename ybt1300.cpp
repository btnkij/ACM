/**
* Number:ybt1300
* Title:鸡蛋的硬度
* Status:AC
* Tag:[dp]
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

const int MAXH=104;
const int MAXN=14;
int dp[MAXN][MAXH];
int solve(int h, int n)
{
    if(h==1)return 1;
    if(dp[h][n])return dp[h][n];
    int &ans = dp[h][n];
    
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    repne(i,1,MAXN)dp[i][1]=1;
    repne(j,1,MAXH)dp[1][j]=j;
    int h,n;
    while(readi2(h,n)!=EOF)
    {
        rep2(i,2,n,j,2,h)
        {
            int tmp=INF;
            rep(k,1,j)
            {
                tmp=min(tmp, max(dp[i-1][k-1], dp[i][j-k]));
            }
            dp[i][j] = tmp + 1;
        }
        printf("%d\n", dp[n][h]);
    }
    return 0;
}