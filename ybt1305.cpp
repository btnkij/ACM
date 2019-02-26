/**
* Number:ybt1305
* Title:Maximum sum
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

const int MAXN=5e4+10;
int num[MAXN];
int dp[MAXN];
int maxfor[MAXN],maxback[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        rep(i,1,n)readi(num[i]);
        for(int i=1;i<=n;i++)
        {
            dp[i]=max(dp[i-1]+num[i], 0);
            maxfor[i]=max(maxfor[i-1], dp[i]);
        }
        dp[n+1]=maxback[n+1]=0;
        for(int i=n;i>=1;i--)
        {
            dp[i]=max(dp[i+1]+num[i], 0);
            maxback[i]=max(maxback[i+1], dp[i]);
        }
        int ans=0;
        repne(i,1,n)ans=max(ans, maxfor[i]+maxback[i+1]);
        printf("%d\n",ans);
    }
    return 0;
}