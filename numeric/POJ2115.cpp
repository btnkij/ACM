/**
* Number:POJ2115
* Title:C Looooops
* Status:AC
* Tag:[exgcd, 数论]
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

ll gcd(ll a,ll b)
{
    if(b==0)return a;
    else return gcd(b,a%b);
}

ll exgcd(ll a,ll& x,ll b,ll& y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    ll r=exgcd(b,y,a%b,x);
    y-=a/b*x;
    return r;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll A,B,C,k;
    while(scanf("%lld %lld %lld %lld",&A,&B,&C,&k)!=EOF && (A|B|C|k))
    {
        ll mod=1LL<<k;
        ll d=gcd(C,mod);
        if((B-A)%d!=0)
        {
            printf("FOREVER\n");
            continue;
        }
        ll x,y;
        mod/=d;
        exgcd(C/d,x,mod,y);
        x*=(B-A)/d, y*=(B-A)/d;
        x=(x%mod+mod)%mod;
        printf("%lld\n",x);
    }
    return 0;
}