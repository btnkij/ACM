/**
* Number:loj10177
* Title:「一本通 5.5 例 3」修剪草坪
* Status:AC
* Tag:[dp, 单调队列]
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Node
{
    ll val;
    int idx;
}Q[100010];
int head,tail;
ll arr[100010],sum;
ll dp[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k; readi(n,k);
    k++;
    rep(i,1,n)
    {
        scanf("%lld",&arr[i]);
        sum+=arr[i];
    }
    Q[tail++]=(Node){0,0};
    rep(i,1,n)
    {
        while(head!=tail && Q[head].idx<i-k)head++;
        dp[i]=Q[head].val+arr[i];
        while(head!=tail && Q[tail-1].val>=dp[i])tail--;
        Q[tail++]=(Node){dp[i],i};
    }
    ll ans=-INF;
    rep(i,n-k+1,n)ans=max(ans,sum-dp[i]);
    printf("%lld",ans);
    return 0;
}