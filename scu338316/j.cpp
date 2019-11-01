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

int sum[110];
int dp[110][110][110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int N,L,R;
    while (readi(N,L,R)!=EOF)
    {
        rep(i,1,N)readi(sum[i]);
        rep(i,1,N)sum[i]+=sum[i-1];
        clr(dp,INF);
        rep2(i,0,N,j,0,N)dp[i][j][0]=0;
        for(int len=L;len<=N;len++)
        {
            for(int lt=1,rt=lt+len-1;rt<=N;lt++,rt++)
            {
                for(int k=1;k<=len;k++)
                {
                    int& f=dp[lt][rt][k];
                    if(k==1 && L<=len && len<=R)
                    {
                        f=sum[rt]-sum[lt-1];
                    }
                    else for(int mid=lt;mid<rt;mid++)
                    {
                        f=min(f,dp[lt][mid][k-1]+dp[mid+1][rt][1]+sum[rt]-sum[lt-1]);
                    }
                }
            }
        }
        int ans=dp[1][N][1];
        printf("%d\n",ans>=INF?0:ans);
    }
    return 0;
}