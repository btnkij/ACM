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

int id[20][20],ladder[110];
double dp[110][2];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int timer=100;
    for(int i=1;i<=10;i+=2)
    {
        for(int j=1;j<=10;j++)id[i][j]=timer--;
        for(int j=10;j>=1;j--)id[i+1][j]=timer--;
    }
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
        {
            int h; readi(h);
            ladder[id[i][j]]=id[i-h][j];
        }
    }
    for(int i=99;i>=94;i--)
    {
        double sum=6;
        for(int j=i+1;j<=100;j++)
        {
            sum+=dp[j][0];
        }
        dp[i][0]=dp[i][1]=sum/(100-i);
    }
    for(int i=93;i>=1;i--)
    {
        double f=0;
        for(int j=1;j<=6;j++)
        {
            f+=dp[i+j][1]+1;
        }
        f/=6;
        dp[i][0]=f;
        dp[i][1]=min(f,dp[ladder[i]][0]);
    }
    printf("%.10lf",dp[1][0]);
    return 0;
}