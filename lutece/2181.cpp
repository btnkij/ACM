/**
* Number:2181
* Title:攻略妹纸
* Status:AC
* Tag:[背包dp]
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
typedef unsigned long long ull;

#define mset(mem, val) memset(mem, val, sizeof(mem))

ll dp[5010][5010];
struct Node
{
    ll cost,charm,val;
    bool operator<(const Node& rhs)const
    {
        return charm<rhs.charm;
    }
}nodes[5010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll n,m,k,x,y;
    scanf("%lld %lld %lld %lld %lld",&n,&m,&k,&x,&y);
    for(ll i=1;i<=n;i++)
    {
        ll a,b,c,d; scanf("%lld %lld %lld %lld",&a,&b,&c,&d);
        nodes[i]=(Node){max(0LL,(c-b)*y), max(0LL,(d-k)*x), a};
    }
    sort(nodes+1,nodes+n+1);
    ll ans=0;
    for(ll i=1;i<=n;i++)
    {
        ll mm=m-nodes[i].charm;
        for(ll j=0;j<=mm;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=nodes[i].cost)
                dp[i][j]=max(dp[i][j], dp[i-1][j-nodes[i].cost]+nodes[i].val);
            ans=max(ans, dp[i][j]);
        }
        
    }
    printf("%lld\n",ans);
    return 0;
}