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

const int MOD=1e9+7;
const int MAXN=310;
int a[MAXN];
ll dp[MAXN*510];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n; readi(n);
        ll sum=0;
        repne(i,0,n)
        {
            readi(a[i]);
            sum+=a[i];
        }
        sort(a,a+n,greater<int>());
        clr(dp,0);
        dp[0]=1;
        for(int i=0;i<n;i++)
        {
            for(int j=sum;j>=a[i];j--)
            {
                if(a[i]>=2*j-sum)
                {
                    dp[j]=(dp[j]+dp[j-a[i]])%MOD;
                }
            }
        }
        ll ans=0;
        for(int i=0;i<=sum;i++)
        {
            if(i>=sum-i)
            {
                ans=(ans+dp[i])%MOD;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}