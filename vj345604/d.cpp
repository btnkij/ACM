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

char s[100010];
ll a[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    reads(s);
    repne(i,0,n)scanf("%lld",a+i);
    ll dp[5][5];
    clr(dp,0);
    repne(i,0,5)dp[i][i]=0;
    repne(x,0,n)
    {
        int sta=0;
        if(s[x]=='h')sta=1;
        else if(s[x]=='a')sta=2;
        else if(s[x]=='r')sta=3;
        else if(s[x]=='d')sta=4;
        if(sta)
        {
            dp[sta][sta-1]+=a[x];
            for(int i=4;i>=0;i--)
            {
                for(int j=i-1;j>=0;j--)
                {
                    for(int k=j;k<=i;k++)
                    {
                        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
                    }
                }
            }
        }
    }
    repne(i,0,5)
    {
        repne(j,0,5)printf("%lld ",dp[i][j]);
        puts("");
    }
    return 0;
}