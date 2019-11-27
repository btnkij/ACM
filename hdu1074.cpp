/**
* Number:hdu1074
* Title:Doing Homework
* Status:AC
* Tag:[状压dp]
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

char name[20][200];
int d[20],c[20],sum[1<<16];
int dp[1<<16],pre[1<<16];
void show(int S)
{
    if(!S)return;
    show(S^(1<<pre[S]));
    printf("%s\n",name[pre[S]]);
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
        repne(i,0,n)
        {
            reads(name[i]);
            readi(d[i],c[i]);
        }
        int all=(1<<n)-1;
        for(int S=1;S<=all;S++)
        {
            int lb=__builtin_ffs(S)-1;
            sum[S]=sum[S^(1<<lb)]+c[lb];
            dp[S]=INF;
            for(int i=0;i<n;i++)
            {
                if(!(S&(1<<i)))continue;
                int tmp=dp[S^(1<<i)]+max(sum[S^(1<<i)]+c[i]-d[i],0);
                if(tmp<=dp[S])dp[S]=tmp,pre[S]=i;
            }
        }
        printf("%d\n",dp[all]);
        show(all);
    }
    return 0;
}