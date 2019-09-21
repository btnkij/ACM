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

const ll MOD=1e9+7;
ll ans;
ll num[3010];
struct{
    // 扩展欧几里得算法
    // 解方程 a*x+b*y==1, 返回 gcd(a,b)
    ll exgcd(ll a, ll& x, ll b, ll& y)
    {
        if(!b)
        {
            x = 1, y = 0;
            return a;
        }
        ll r = exgcd(b, y, a % b, x);
        y -= a / b * x;
        return r;
    }
    ll operator()(ll a, ll mod)
    {
        ll x, y;
        exgcd(a, x, mod, y);
        if(x < 0)x += mod;
        return x;
    }
}inv;
ll calc(int n,int dep)
{
    ll ans=1;
    int pre=num[0],cnt=0;
    repne(i,0,dep)
    {
        if(num[i]==pre)cnt++;
        else
        {
            for(int i=0;i<cnt;i++)
                ans=ans*(n-i)%MOD;
            for(int i=2;i<=cnt;i++)
                ans=ans*inv(i,MOD)%MOD;
            n-=cnt;
            cnt=1;
            pre=num[i];
        }
    }
    if(cnt>0)
    {
        for(int i=0;i<cnt;i++)
            ans=ans*(n-i)%MOD;
        for(int i=2;i<=cnt;i++)
            ans=ans*inv(i,MOD)%MOD;
    }
    return ans;
}
void dfs(int pre,ll sum,ll prod,int dep,int maxdep)
{
    if(dep==maxdep)
    {
        if(sum!=prod)return;
        // repne(i,0,maxdep)printf("%lld ",num[i]);
        // puts("");
        ans=(ans+calc(maxdep,dep));
        return;
    }
    if(sum+maxdep-dep==prod)
    {
        // repne(i,0,dep)printf("%lld ",num[i]);
        // repne(i,dep,maxdep)printf("1 ");
        // puts("");
        ans=(ans+calc(maxdep,dep))%MOD;
        return;
    }
    for(int i=2;i<=pre;i++)
    {
        if(sum+i+maxdep-dep-1<prod*i)break;
        num[dep]=i;
        dfs(i,sum+i,prod*i,dep+1,maxdep);
    }
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
        int n; readi(n);
        ans=0;
        dfs(n,0,1,0,n);
        printf("%lld\n",ans);
    }
    return 0;
}