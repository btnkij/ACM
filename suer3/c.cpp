#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f3f3f3f3fLL
#define PI acos(-1)
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

int w[20],h[20],num[20],maxw[1<<18],maxh[1<<18];
ll dp[20][1<<18];
bool vis[20][1<<18];
ll solve(int n,int S)
{
    if(vis[n][S])return dp[n][S];
    if(n==1)
    {
        ll ans=0;
        ll area=(ll)maxw[S]*maxh[S];
        for(int i=0;i<16;i++)
        {
            if(S&(1<<i))
            {
                ans+=(area-w[i]*h[i])*num[i];
            }
        }
        vis[n][S]=true;
        return dp[n][S]=ans;
    }
    if(n>=1 && (S&(S-1))==0)
    {
        vis[n][S]=true;
        return dp[n][S]=0;
    }
    if(n==0 && S)
    {
        vis[n][S]=true;
        return dp[n][S]=INF;
    }
    ll tmp=INF;
    for(int sub=(S-1)&S; sub; sub=(sub-1)&S)
    {
        int com=S^sub;
        tmp=min(tmp,solve(n-1,sub)+solve(1,com));
    }
    vis[n][S]=true;
    return dp[n][S]=tmp;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,0,n)readi(w[i],h[i],num[i]);
    int all=(1<<n)-1;
    for(int i=0;i<=all;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(i&(1<<j))
            {
                maxw[i]=max(maxw[i],w[j]);
                maxh[i]=max(maxh[i],h[j]);
            }
        }
    }
    printf("%lld",solve(m,all));
    return 0;
}