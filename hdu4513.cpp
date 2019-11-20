/**
* Number:hdu4513
* Title:吉哥系列故事——完美队形II
* Status:AC
* Tag:[manacher]
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

const int MAXN=2e5+10;
int dp[MAXN],s[MAXN];
void manacher(int len)
{
    int p,far=0;
    repne(i,0,len)
    {
        int l,r;
        r = i>=far ? i+1 : min(far+1, i+dp[p*2-i]);
        l=i*2-r;
        while(l>=0 && s[l]==s[r] && s[l]<=s[l+2])l--,r++;
        dp[i]=r-i;
        if(r-1>far)far=r-1,p=i;
    }
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
        int n; readi(n);
        int len=n*2+1;
        for(int i=0;i<len;i++)
        {
            if(i&1)readi(s[i]);
            else s[i]=-1;
        }
        manacher(len);
        printf("%d\n",*max_element(dp,dp+len)-1);
    }
    return 0;
}