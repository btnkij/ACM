/**
* Number:hdu5773
* Title:The All-purpose Zero 
* Status:AC
* Tag:[LIS, 贪心]
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

int dp[100010],tot,ans;
void append(int x)
{
    if(tot==0)
    {
        dp[0]=x;
        tot=ans=1;
        return;
    }
    int i=tot;
    while(i>=1 && dp[i-1]>=x)i--;
    dp[i]=x;
    tot=max(tot,i+1);
    ans=max(ans,tot);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    rep(kase,1,T)
    {
        tot=ans=0;
        int n; readi(n);
        int cnt=0;
        while(n--)
        {
            int t; readi(t);
            if(t==0)cnt++;
            else append(t-cnt);
        }
        printf("Case #%d: %d\n",kase,ans+cnt);
    }
    return 0;
}