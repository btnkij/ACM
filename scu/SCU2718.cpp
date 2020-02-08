/**
* Number:scu2718
* Title:Bookshelf
* Status:AC
* Tag:[区间dp]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int dp[110][110];
int h[110];
int maxv[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k;
    while(readi(n,k)!=EOF && n && k)
    {
        rep(i,1,n)readi(h[i]);
        mset(dp,0);
        rep(i,1,n)dp[i][1]=max(dp[i-1][1], h[i]);
        for(int L=2;L<=k;L++)
        {
            for(int b=L;b<=n;b++)
            {
                mset(maxv,0);
                maxv[b+1]=-INF;
                for(int k=b;k>=L;k--)
                    maxv[k]=max(maxv[k+1], h[k]);
                dp[b][L]=INF;
                for(int k=L;k<=b;k++)
                {
                    dp[b][L] = min(dp[b][L], dp[k-1][L-1]+maxv[k]);
                }
            }
        }
        printf("%d\n",dp[n][k]);
    }
    return 0;
}