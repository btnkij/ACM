/**
* Number:scu4119
* Title:Function
* Status:AC
* Tag:[数论]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

ll f(ll x)
{
    return x^x+1;
}
ll count(ll x)
{
    ll ans=0,i=0;
    while(true)
    {
        ll mask=(1<<i)-1;
        if(mask>x)break;
        ans+=((x-(1<<i)+1)/(2<<i)+1)*(i+1);
        // printf("%lld %lld\n",i,((x-(1<<i)+1)/(2<<i)+1));
        i++;
    }
    return ans;
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
        ll a,b; scanf("%lld %lld",&a,&b);
        if(a==0)
        {
            printf("%lld\n",count(b));
        }
        else
        {
            printf("%lld\n",count(b)-count(a-1));
        }
    }
    return 0;
}