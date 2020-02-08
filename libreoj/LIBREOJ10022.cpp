/**
* Number:loj10022
* Title:「一本通 1.3 练习 1」埃及分数
* Status:AC
* Tag:[dfs]
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

ll gcd(ll a,ll b)
{
    return b==0 ? a : gcd(b,a%b);
}
ll A,B;
ll ans[1010], tmp[1010];
int len, len1;
void dfs(ll a, ll b, int dep)
{
    // printf("%lld %lld %d\n",a,b,dep);
    if(dep==0)
    {
        if(A*b==B*a && (len==-1 || ans[len1-1]>tmp[len1-1]))
        {
            copy(tmp,tmp+len1,ans);
            len=len1;
        }
        return;
    }
    ll pre=len1>0?tmp[len1-1]:1;
    pre=max(B*b/(A*b-B*a), pre+1);
    for(ll c=pre;;c++)
    {
        if(a*B*c+dep*B*b<A*b*c)return;
        ll nxta=a*c+b, nxtb=b*c;
        if(nxta*B>nxtb*A)continue;
        tmp[len1++]=c;
        dfs(a*c+b,b*c,dep-1);
        len1--;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%lld %lld",&A,&B);
    len=-1;
    for(int i=2;len==-1;i++)
    {
        dfs(0,1,i);
    }
    repne(i,0,len)printf("%d ",ans[i]);
    return 0;
}