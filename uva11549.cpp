/**
* Number:uva11549
* Title:Calculator Conundrum
* Status:AC
* Tag:[floyd判圈]
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

char num[100];
ll mod(ll k,int n)
{
    sprintf(num,"%lld",k);
    num[n]='\0';
    sscanf(num,"%lld",&k);
    return k;
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
        int n; ll k; scanf("%d %lld",&n,&k);
        ll k1=k, k2=k;
        ll ans=k;
        do
        {
            k1=mod(k1*k1,n);
            k2=mod(k2*k2,n); ans=max(ans,k2);
            k2=mod(k2*k2,n); ans=max(ans,k2);
        }while(k1!=k2);
        printf("%lld\n",ans);
    }
    return 0;
}