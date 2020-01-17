/**
* Number:poj1661
* Title:Help Jimmy
* Status:AC
* Tag:[dp]
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

int n,m;
int x[1010][2],h[1010];
int dp[1010][2];
int dfs(int i,int d)
{
    if(~dp[i][d])return dp[i][d];
    int k,tmp=0;
    rep(j,1,n)
    {
        if(x[j][0]>x[i][d] || x[j][1]<x[i][d])continue;
        if(h[i]<=h[j] || h[i]-h[j]>m)continue;
        if(h[j]>tmp)tmp=h[j],k=j;
    }
    if(tmp>0)
    {
        return dp[i][d]=h[i]-h[k]+min(
            abs(x[i][d]-x[k][0])+dfs(k,0),
            abs(x[i][d]-x[k][1])+dfs(k,1)
        );
    }
    else if(h[i]<=m)
    {
        return dp[i][d]=h[i];
    }
    return INF;
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
        int sx,sy;
        readi(n,sx,sy,m);
        x[0][0]=x[0][1]=sx,h[0]=sy;
        rep(i,1,n)readi(x[i][0],x[i][1],h[i]);
        clr(dp,-1);
        printf("%d\n",dfs(0,0));
    }
    return 0;
}