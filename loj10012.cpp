/**
* Number:loj10012
* Title:「一本通 1.2 例 2」Best Cow Fences
* Status:AC
* Tag:[二分, dp]
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
#define eps 1e-4
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

int n,L;
double a[100010];
double dp[100010], sum[100010];
bool check(double mid)
{
    rep(i,1,n)
    {
        sum[i]=sum[i-1]+a[i]-mid;
    }
    dp[L-1]=sum[L-1];
    rep(i,L,n)
    {
        dp[i]=max(sum[i-1]-sum[i-L], dp[i-1])+a[i]-mid;
        if(dp[i]>=0)return true;
    }
    return false;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,L);
    double lt=1e10, rt=-1e10;
    rep(i,1,n)
    {
        scanf("%lf",a+i);
        lt=min(lt,a[i]);
        rt=max(rt,a[i]);
    }
    while(rt-lt>eps)
    {
        double mid=(lt+rt)/2;
        if(check(mid))lt=mid;
        else rt=mid;
    }
    printf("%d",(int)(rt*1000));
    return 0;
}