/**
* Number:ybt1302
* Title:股票买卖
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

const int MAXN=1e5+4;
int cost[MAXN];
ll dpfor[MAXN],dpback[MAXN];
ll maxfor[MAXN],maxback[MAXN];
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
        rep(i,1,n)readi(cost[i]);
        for(int i=n;i>0;i--)cost[i]-=cost[i-1];
        for(int i=2;i<=n;i++)
        {
            dpfor[i]=max(cost[i]+dpfor[i-1], 0LL);
            maxfor[i]=max(maxfor[i-1], dpfor[i]);
        }
        dpback[n+1]=maxback[n+1]=0LL;
        for(int i=n;i>=2;i--)
        {
            dpback[i]=max(cost[i]+dpback[i+1], 0LL);
            maxback[i]=max(maxback[i+1], dpback[i]);
        }
        ll ans=0;
        rep(i,1,n)ans=max(ans, maxfor[i]+maxback[i+1]);
        printf("%lld\n",ans);
    }
    return 0;
}