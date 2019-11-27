/**
* Number:hdu1176
* Title:免费馅饼
* Status:AC
* Tag:[dp]
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

int dp[100010][20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF && n)
    {
        clr(dp,0);
        int maxt=-INF;
        repne(i,0,n)
        {
            int x,t; readi(x,t);
            dp[t][x]+=1;
            maxt=max(maxt,t);
        }
        for(int i=maxt;i>=0;i--)
        {
            dp[i][0]+=max(dp[i+1][0],dp[i+1][1]);
            for(int j=1;j<=9;j++)
            {
                dp[i][j]+=max(dp[i+1][j-1],max(dp[i+1][j],dp[i+1][j+1]));
            }
            dp[i][10]+=max(dp[i+1][9],dp[i+1][10]);
        }
        printf("%d\n",dp[0][5]);
    }
    return 0;
}