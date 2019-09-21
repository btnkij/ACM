#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
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
    int T; readi(T);
    rep(kase,1,T)
    {
        ll a,b,c,d,p,m;
        scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&c,&d,&p,&m);
        b=b-a;
        d=d-c;
        m=((m-a-c)%p+p)%p;
        ll lmid=min(b,d);
        ll rmid=b+d-lmid;
        if(lmid>=rmid)rmid=lmid+1;
        ll up=0;
        ll a1=m;
        ll cnt=(lmid-m)/p+1;
        if(a1<=lmid)
        {
            a1=a1+1;
            up+=cnt*a1+cnt*(cnt-1)/2*p;
        }
        a1=(b+d)/p*p+m;
        cnt=(a1-rmid)/p+1;
        if(a1<=b+d && a1>=rmid)
        {
            a1=b+d-a1+1;
            up+=cnt*a1+cnt*(cnt-1)/2*p;
        }
        if(lmid+1<=rmid-1)
        {
            a1=(lmid+1)/p*p+m;
            if(lmid+1<=a1 && a1<=rmid-1)
            {
                cnt=(rmid-a1-1)/p+1;
                up+=cnt*min(b+1,d+1);
            }
        }
        ll down=(ll)(b+1)*(d+1);
        ll g=gcd(up,down);
        printf("Case #%d: %lld/%lld\n",kase,up/g,down/g);
    }
    return 0;
}