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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const ll MOD=1e9+7;
ll dp[110][10010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,w,h; readi(n,w,h);
    int mm=min(n,h);
    for(int i=0;i<=mm;i++)dp[1][i]=i+1;
    for(int i=mm+1;i<=n;i++)dp[1][i]=dp[1][mm];
    for(int i=2;i<=w;i++)
    {
        for(int j=0;j<=h;j++)
        {
            for(int k=h;k<=n;k++)
            {
                dp[i][k]=(dp[i-1][k-j]+j+1)%MOD;
            }
        }
    }
    ll ans=dp[w][n]-n/w-1;
    for(int i=1;i<=w;i++)ans=ans*i%MOD;
    printf("%lld",ans);
    return 0;
}