/**
* Number:ybt1303
* Title:鸣人的影分身
* Status:AC
* Tag:[记忆化搜索]
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=14;
ll dp[MAXN][MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN];
ll solve(int m,int n, int pre)
{
    if(m==0 || n==1)return 1;
    if(vis[m][n][pre])return dp[m][n][pre];
    vis[m][n][pre]=true;
    ll &ans=dp[m][n][pre];
    for(int i=min(pre, m); i>=0 && i*n>=m; i--)
    {
        ans+=solve(m-i, n-1, i);
    }
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
        int m,n;
        readi2(m,n);
        printf("%lld\n",solve(m,n,m));
    }
    return 0;
}