/**
* Number:cf1285c
* Title:Fadi and LCM
* Status:AC
* Tag:[唯一分解, 集合枚举]
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

vector<ll> factor;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll x; scanf("%lld",&x);
    if(x==1)
    {
        printf("1 1");
    }
    else
    {
        ll tmp=x;
        for(ll i=2;i*i<=tmp && tmp>1;i++)
        {
            ll f=1;
            while(tmp%i==0)
            {
                f*=i;
                tmp/=i;
            }
            if(f!=1)factor.push_back(f);
        }
        if(tmp>1)factor.push_back(tmp);
        if(factor.size()==1)printf("1 %lld",factor[0]);
        else
        {
            ll a=1,b=x;
            ll all=(1<<factor.size())-1;
            for(ll S=1;S<=all;S++)
            {
                ll tmp=1;
                repne(i,0,factor.size())
                {
                    if(S&(1<<i))tmp*=factor[i];
                }
                if(max(tmp,x/tmp)<b)
                {
                    b=max(tmp,x/tmp);
                    a=x/b;
                }
            }
            printf("%lld %lld",a,b);
        }
    }
    return 0;
}