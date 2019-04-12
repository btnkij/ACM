/**
* Number:loj10158
* Title:「一本通 5.2 练习 1」加分二叉树 
* Status:AC
* Tag:[区间dp]
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

#define INF 0x3f3f3f3f3f3f3f3fLL
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

ll dp[40][40];
void traceback(int lt,int rt)
{
    if(lt>rt)return;
    if(lt==rt)
    {
        printf("%d ",lt);
        return;
    }
    ll ans=dp[lt][rt];
    rep(k,lt,rt)
    {
        if(dp[lt][k-1]*dp[k+1][rt]+dp[k][k] == ans)
        {
            printf("%d ",k);
            traceback(lt,k-1);
            traceback(k+1,rt);
            break;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep2(i,0,n+1,j,0,n+1)dp[i][j]=1;
    rep(i,1,n)scanf("%lld", &dp[i][i]);
    for(int L=2;L<=n;L++)
    {
        for(int lt=1,rt=lt+L-1; rt<=n; lt++, rt++)
        {
            ll tmp=-INF;
            for(int k=lt;k<=rt;k++)
            {
                tmp=max(tmp,dp[lt][k-1]*dp[k+1][rt]+dp[k][k]);
            }
            dp[lt][rt]=tmp;
        }
    }
    printf("%lld\n",dp[1][n]);
    traceback(1,n);
    return 0;
}