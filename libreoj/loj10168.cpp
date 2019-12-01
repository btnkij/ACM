/**
* Number:loj10168
* Title:「一本通 5.3 练习 3」恨 7 不成妻
* Status:AC
* Tag:[数位dp]
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

const int MOD=1e9+7;
ll base[20];
vector<int> num;
bool vis[20][10][10];
struct tri
{
    ll cnt,sum,sum2;
}dp[20][10][10];
tri dfs(int dep,int bitsum,int val,bool bound)
{
    if(dep==-1)return (tri){bitsum&&val,0,0};
    if(!bound && vis[dep][bitsum][val])
    {
        return dp[dep][bitsum][val];
    }
    int lim=bound?num[dep]:9;
    tri ans=(tri){0,0,0};
    for(int i=0;i<=lim;i++)
    {
        if(i==7)continue;
        tri res=dfs(dep-1,(bitsum+i)%7,(val*10+i)%7,bound&&i==lim);
        if(res.cnt==0)continue;
        ll wi=i*base[dep]%MOD;
        ans.cnt=(ans.cnt+res.cnt)%MOD;
        ans.sum=(ans.sum+wi*res.cnt%MOD+res.sum)%MOD;
        ans.sum2=(ans.sum2+wi*wi%MOD*res.cnt%MOD+res.sum2+2*wi%MOD*res.sum%MOD)%MOD;
    }
    if(!bound)
    {
        vis[dep][bitsum][val]=true;
        dp[dep][bitsum][val]=ans;
    }
    return ans;
}
ll query(ll x)
{
    num.clear();
    for(;x;x/=10)num.push_back(x%10);
    return dfs(num.size()-1,0,0,true).sum2;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    base[0]=1;
    repne(i,1,20)base[i]=base[i-1]*10%MOD;
    int T; readi(T);
    while(T--)
    {
        ll L,R; scanf("%lld %lld",&L,&R);
        ll ans=((query(R)-query(L-1))%MOD+MOD)%MOD;
        printf("%lld\n",ans);
    }
    return 0;
}