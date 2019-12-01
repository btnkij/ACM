/**
* Number:loj10169
* Title:「一本通 5.3 练习 4」数字计数
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

vector<int> num;
ll dp[20][20];
ll dfs(int dep,int cnt,bool zero,bool bound,int b)
{
    if(dep==-1)return cnt;
    if(!zero && !bound && dp[dep][cnt]!=-1)return dp[dep][cnt];
    int lim=bound?num[dep]:9;
    ll ans=0;
    for(int i=0;i<=lim;i++)
    {
        int nxtcnt;
        if(i!=b || i==b && b==0 && zero)nxtcnt=cnt;
        else nxtcnt=cnt+1;
        bool nxtzero=zero&&i==0;
        bool nxtbound=bound&&i==lim;
        ans+=dfs(dep-1,nxtcnt,nxtzero,nxtbound,b);
    }
    if(!zero && !bound)dp[dep][cnt]=ans;
    return ans;
}
ll query(ll x,int b)
{
    num.clear();
    for(;x;x/=10)num.push_back(x%10);
    clr(dp,-1);
    return dfs(num.size()-1,0,true,true,b);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll a,b; scanf("%lld %lld",&a,&b);
    rep(i,0,9)printf("%lld ",query(b,i)-query(a-1,i));
    return 0;
}