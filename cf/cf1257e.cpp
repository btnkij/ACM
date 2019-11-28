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

const int MAXN=200010;
int sum1[MAXN],sum2[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int k[3]; readi(k[0],k[1],k[2]);
    int n=k[0]+k[1]+k[2];
    rep(i,1,k[0])
    {
        int t; readi(t);
        sum1[t]-=1, sum2[t]-=1;
    }
    rep(i,1,k[1])
    {
        int t; readi(t);
        sum1[t]+=1, sum2[t]-=2;
    }
    rep(i,1,k[2])
    {
        int t; readi(t);
    }
    rep(i,1,n)
    {
        sum1[i]+=sum1[i-1];
        sum2[i]+=sum2[i-1];
    }
    rep(i,1,n)sum2[i]+=i;
    for(int i=n-1;i>=0;i--)sum2[i]=min(sum2[i],sum2[i+1]);
    int ans=INF;
    for(int i=0;i<=n;i++)
    {
        // len1-x1+min(len2-(sum2-x2)+k1+k2-sum1-sum2)
        // k1+k2-x1+x2+min(len1+len2-sum1-sum2-sum2)
        ans=min(ans,k[0]+k[1]+sum1[i]+sum2[i]);
    }
    printf("%d\n",ans);
    return 0;
}