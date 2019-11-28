/**
* Number:cf1245f
* Title:Daniel and Spring Cleaning
* Status:AC
* Tag:[容斥, 数位dp]
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

ll dp[40][2][2];
ll dfs(int x,int y,int k,int boundx,int boundy)
{
    if(x==-1 || y==-1)return 0;
    if(k==-1)return 1;
    if(dp[k][boundx][boundy]!=-1)return dp[k][boundx][boundy];
    int limx=boundx?(x>>k)&1:1, limy=boundy?(y>>k)&1:1;
    ll ans=0;
    for(int i=0;i<=limx;i++)
    {
        for(int j=0;j<=limy;j++)
        {
            if((i&j)==0)
            {
                ans+=dfs(x,y,k-1,boundx&&i==limx,boundy&&j==limy);
            }
        }
    }
    return dp[k][boundx][boundy]=ans;
}
ll solve(int l,int r)
{
    clr(dp,-1);
    ll ans=dfs(l,r,30,true,true);
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
        int l,r; readi(l,r);
        ll ans=
            solve(r,r)
            -solve(l-1,r)
            -solve(r,l-1)
            +solve(l-1,l-1);
        printf("%lld\n",ans);
    }
    return 0;
}