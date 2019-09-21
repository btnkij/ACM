/**
* Number:hdu6641
* Title:TDL
* Status:AC
* Tag:[规律, 枚举]
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

#define INF 0x7f7f7f7f7f7f7f7f
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

ll gcd(ll a,ll b)
{
    return b==0 ? a : gcd(b,a%b);
}
bool check(ll n,ll m,ll k)
{
    ll b=n;
    while(m)
    {
        b++;
        if(gcd(n,b)==1)m--;
    }
    if(b-n>500)throw;
    return ((b-n)^n)==k;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        ll k,m; scanf("%lld %lld",&k,&m);
        ll ans=INF;
        for(ll i=1;i<=800;i++)
        {
            ll n=k^i;
            if(n==0 || n>=ans)continue;
            if(check(n,m,k))ans=min(ans,n);
        }
        if(ans!=INF)printf("%lld\n",ans);
        else printf("-1\n");
    }
    return 0;
}