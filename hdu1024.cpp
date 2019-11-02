/**
* Number:hdu1024
* Title:Max Sum Plus Plus
* Status:?
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

ll arr[1000010],dp[2][1000010][2];
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
        dp[cur][1][0]=-INF, dp[cur][1][1]=arr[1];
        for(int i=2;i<=n;i++)
        {
            swap(pre,cur);
            int maxj=min(i,m);
            for(int j=1;j<=maxj;j++)
            {
                dp[cur][j][0]=max(dp[pre][j][0],dp[pre][j][1]);
                dp[cur][j][1]=max(dp[pre][j-1][0],dp[pre][j-1][1])+arr[i];
                if(i-1>=j)dp[cur][j][1]=max(dp[cur][j][1],dp[pre][j][1]+arr[i]);
            }
        }
        printf("%lld\n",max(dp[cur][m][0],dp[cur][m][1]));
    }
    return 0;
}