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

#define INF 0x3f3f3f3f3f3f3f3fLL
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

char s[100010];
ll a[100010];
ll dp[100010][5];
char hard[]="hard";
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    reads(s+1);
    rep(i,1,n)scanf("%lld",a+i);
    rep(i,0,n)dp[i][0]=INF;
    rep(i,1,4)dp[0][i]=0;
    rep(i,1,n)
    {
        rep(j,1,4)
        {
            if(s[i]==hard[j-1])
                dp[i][j]=min(dp[i-1][j-1],dp[i-1][j]+a[i]);
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    printf("%lld\n",dp[n][4]);
    return 0;
}