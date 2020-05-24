/**
* Number:CF1334D
* Title:Minimum Euler Cycle
* Status:AC
* Tag:[构造]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        ll n,l,r;
        scanf("%lld %lld %lld",&n,&l,&r);
        if(l==n*(n-1)+1)
        {
            puts("1");
            continue;
        }
        ll len=r-l+1;
        ll lt=1,rt=n-1;
        while(lt<rt)
        {
            ll mid=(lt+rt)>>1;
            if((2*n-mid-1)*mid<l)lt=mid+1;
            else rt=mid;
        }
        ll a=lt;
        ll b=a+ceil((l-(2*n-a)*(a-1))/2.);
        if(l%2==0)
        {
            printf("%d ",b++);
            len--;
        }
        while(len>0)
        {
            if(b>n)
            {
                a++;
                b=a+1;
                if(a>=n)a=1;
            }
            if(len)
            {
                printf("%lld ",a);
                len--;
            }
            if(len)
            {
                printf("%lld ",b);
                len--;
                b++;
            }
        }
        puts("");
    }
    return 0;
}