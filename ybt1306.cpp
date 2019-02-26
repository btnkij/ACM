/**
* Number:ybt1306
* Title:最长公共子上升序列
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

const int MAXN=504;
int n1,n2;
int num1[MAXN],num2[MAXN];
int dp[MAXN][MAXN];
int pre[MAXN][MAXN];
void showpath(int i,int j)
{
    if(j==0)return;
    while(pre[i][j]==j)i--;
    showpath(i,pre[i][j]);
    printf("%d ",num2[j]);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n1);
    rep(i,1,n1)readi(num1[i]);
    readi(n2);
    rep(i,1,n2)readi(num2[i]);
    int ans=0,ansj;
    for(int i=1;i<=n1;i++)
    {
        int maxdp=0,maxidx=0;
        for(int j=1;j<=n2;j++)
        {
            if(num1[i]>num2[j] && maxdp<dp[i-1][j])
                maxdp=dp[i-1][j], maxidx=j;
            if(num1[i]==num2[j])
                dp[i][j]=maxdp+1, pre[i][j]=maxidx;
            else
                dp[i][j]=dp[i-1][j], pre[i][j]=j;
            if(dp[i][j]>ans)
            {
                ans=dp[i][j];
                ansj=j;
            }
        }
    }
    printf("%d\n",ans);
    showpath(n1,ansj);
    return 0;
}