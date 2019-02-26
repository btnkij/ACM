/**
* Number:uva12325
* Title:Zombie's Treasure Chest
* Status:?
* Tag:[枚举, 分类枚举]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

ll n,s[2],v[2];
int main()
{
    int T; scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%lld %lld %lld %lld %lld",&n,&s[0],&v[0],&s[1],&v[1]);
        ll ans=0;
        if(s[0]>s[1])
        {
            swap(s[0],s[1]); swap(v[0],v[1]);
        }
        if(n/s[1]<65536)
            for(ll i=0; s[1]*i<=n; i++)
                ans=max(ans,v[1]*i+(n-s[1]*i)/s[0]*v[0]);
        else
        {
            for(ll i=0; i<=s[0]; i++)
                ans=max(ans,v[1]*i+(n-i*s[1])/s[0]*v[0]);
            for(ll i=0; i<=s[1]; i++)
                ans=max(ans,v[0]*i+(n-i*s[0])/s[1]*v[1]);
        }
        printf("Case #%d: %lld\n",kase,ans);
    }
    return 0;
}