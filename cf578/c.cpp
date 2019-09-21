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
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll n,m,q; scanf("%lld %lld %lld",&n,&m,&q);
    ll d=gcd(n,m);
    ll d1=n/d,d2=m/d;
    while(q--)
    {
        ll sx,sy,ex,ey; scanf("%lld %lld %lld %lld",&sx,&sy,&ex,&ey);
        sy--, ey--;
        ll p1= sx==1 ? sy/d1 : sy/d2;
        ll p2= ex==1 ? ey/d1 : ey/d2;
        printf("%s\n",p1==p2 ? "YES" : "NO");
    }
    return 0;
}