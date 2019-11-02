/**
* Number:hdu1024
* Title:Max Sum Plus Plus
* Status:AC
* Tag:[dp, 滚动数组]
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

#define INF 0x3f3f3f3f3f3f3f3fLL
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

const int MAXN=1e6+10;
ll arr[MAXN],dp[2][MAXN][2];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m,n;
    while(readi(m,n)!=EOF)
    {
        rep(i,1,n)scanf("%lld",arr+i);
        int pre=0,cur=1;
        rep(i,0,m)dp[cur][i][0]=dp[cur][i][1]=-INF;
        dp[cur][0][0]=0;
        for(int i=1;i<=n;i++)
        {
            swap(pre,cur);
            rep(i,0,m)dp[cur][i][0]=dp[cur][i][1]=-INF;
            dp[cur][0][0]=0;
            for(int j=1;j<=m;j++)
            {
                dp[cur][j][0]=max(dp[pre][j][0],dp[pre][j][1]);
                dp[cur][j][1]=max(dp[pre][j-1][0],max(dp[pre][j-1][1],dp[pre][j][1]))+arr[i];
            }
        }
        printf("%lld\n",max(dp[cur][m][0],dp[cur][m][1]));
    }
    return 0;
}