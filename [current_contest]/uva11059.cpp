/**
* Number:uva11059
* Title:Maximum Product
* Status:AC
* Tag:[枚举, 暴力]
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

#define INF 0x7fffffffffffffffLL
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

ll a[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,kase=1;
    while(readi(n)!=EOF)
    {
        a[0]=1;
        rep(i,1,n)scanf("%lld",a+i);
        rep(i,1,n)if(a[i-1])a[i]*=a[i-1];
        ll ans=0;
        rep(i,1,n)
        {
            if(a[i]==0)
            {
                a[i]=1;
                continue;
            }
            rep(j,i,n)
            {
                if(a[j]==0)break;
                ans=max(ans,a[j]/a[i-1]);
            }
        }
        printf("Case #%d: The maximum product is %lld.\n\n",kase++,ans);
    }
    return 0;
}