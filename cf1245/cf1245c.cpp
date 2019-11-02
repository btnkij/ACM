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

const ll MOD=1e9+7;
char s[100010];
ll dp[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    dp[1]=1, dp[2]=2;
    for(int i=3;i<100005;i++)
    {
        dp[i]=(dp[i-1]+dp[i-2])%MOD;
    }
    while(reads(s)!=EOF)
    {
        int len=strlen(s);
        if(find(s,s+len,'m')!=s+len || find(s,s+len,'w')!=s+len)
        {
            puts("0");
            continue;
        }
        int u,n;
        ll ans=1;
        int i=0;
        while(i<len)
        {
            if(s[i]=='u' || s[i]=='n')
            {
                int cnt=0;
                while(i+cnt<len && s[i+cnt]==s[i])cnt++;
                ans=ans*dp[cnt]%MOD;
                i+=cnt;
            }
            else i++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}