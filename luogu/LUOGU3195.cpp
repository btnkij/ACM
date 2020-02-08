/**
* Number:p3195
* Title:[HNOI2008]玩具装箱TOY /【模板】斜率优化
* Status:AC
* Tag:[斜率优化dp]
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

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 5e4 + 10;
ll dp[MAXN], sum[MAXN], f[MAXN], g[MAXN];
int Q[MAXN], head, tail;
inline ll sq(ll x)
{
    return x * x;
}
inline double slope(int a, int b)
{
    return (double)(g[a] - g[b]) / (f[a] - f[b]);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    sum[i]
    dp[i]=min dp[j]+(sum[i]-sum[j]+i-j-1-L)^2
    dp[i]=min dp[j]+((sum[i]+i)-(sum[j]+j)-L-1)^2
    f[i]=sum[i]+i
    dp[i]=min dp[j]+(f[i]-f[j]-L-1)^2
    dp[a]+(f[i]-f[a]-L-1)^2 <= dp[b]+(f[i]-f[b]-L-1)^2
    dp[a]+f[i]^2-2*f[i]*(f[a]+L+1)+(f[a]+L+1)^2 <= dp[b]+f[i]^2-2*f[i]*(f[b]+L+1)+(f[b]+L+1)^2
    dp[a]-2*f[i]*f[a]+(f[a]+L+1)^2 <= dp[b]-2*f[i]*f[b]+(f[b]+L+1)^2
    2*f[i]*(f[b]-f[a]) <= dp[b]+(f[b]+L+1)^2 - dp[a]-(f[a]+L+1)^2
    g[x]=dp[x]+(f[x]+L+1)^2
    suppose a>b, then f[a]-f[b]>0
    a is better iff 2*f[i] >= (g[a]-g[b])/(f[a]-f[b])
    */
    int n, L;
    readi(n, L);
    rep(i, 1, n)
    {
        scanf("%lld", sum + i);
        sum[i] += sum[i - 1];
        f[i] = sum[i] + i;
    }
    dp[0] = f[0] = 0, g[0] = sq(L + 1);
    head = tail = 0, Q[tail++] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (tail - head > 1 && slope(Q[head + 1], Q[head]) <= 2 * f[i])
            head++;
        dp[i] = dp[Q[head]] + sq(f[i] - f[Q[head]] - L - 1);
        g[i] = dp[i] + sq(f[i] + L + 1);
        while (tail - head > 1 && slope(i, Q[tail - 1]) <= slope(Q[tail - 1], Q[tail - 2]))
            tail--;
        Q[tail++] = i;
    }
    printf("%lld\n", dp[n]);
    return 0;
}