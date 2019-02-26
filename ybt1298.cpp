/**
* Number:ybt1298
* Title:计算字符串距离
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

char s1[1010],s2[1010];
int dp[1010][1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T;readi(T);
    while(T--)
    {
        scanf("%s %s",s1+1,s2+1);
        int len1=strlen(s1+1),len2=strlen(s2+1);
        rep(i,0,len1)dp[i][0]=i;
        rep(j,0,len2)dp[0][j]=j;
        rep2(i,1,len1,j,1,len2)
        {
            if(s1[i]==s2[j])dp[i][j]=dp[i-1][j-1];
            else
            {
                int tmp=min(dp[i-1][j],dp[i][j-1]);
                tmp=min(tmp,dp[i-1][j-1]);
                dp[i][j]=tmp+1;
            }   
        }
        printf("%d\n",dp[len1][len2]);
    }
    return 0;
}