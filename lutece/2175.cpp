/**
* Number:2175
* Title:手办
* Status:AC
* Tag:[01背包, 状压dp]
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int height[105];
int dp[2][10][1<<8][105];
int S[1<<9],len;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int kase=1;
    int n,k;
    while(readi(n,k)!=EOF && n && k)
    {
        int all=0;
        rep(i,1,n)
        {
            readi(height[i]);
            height[i]-=114514;
            all|=1<<height[i];
        }
        int V=n-k;
        if(V==0)
        {
            int cnt=0;
            for(int i=0;i<8;i++)
                if(all&(1<<i))cnt++;
            printf("Case %d: %d\n\n",kase++,cnt);
            continue;
        }
        if(!(all&(all-1)))
        {
            printf("Case %d: 1\n\n",kase++);
            continue;
        }
        len=0;
        for(int sta=all;sta;sta=(sta-1)&all)
            S[len++]=sta;
        S[len]=0;
        int pre=0, cur=1;
        mset(dp[0],INF);
        repne(h,0,8)dp[0][h][0][0]=1;
        for(int i=1;i<=n;i++)
        {
            mset(dp[cur],INF);
            int h1=height[i];
            for(int h=0;h<8;h++)
            {
                int val=(int)(h1!=h);
                for(int s=len;s>=0;s--)
                {
                    int sta=S[s];
                    int *curdp0=dp[cur][h][sta],*curdp1=dp[cur][h1][sta|(1<<h1)];
                    int *predp=dp[pre][h][sta];
                    int mm=min(i,V);
                    curdp0[0]=min(curdp0[0],predp[0]);
                    for(int j=1;j<=mm;j++)
                    {
                        curdp0[j]=min(curdp0[j],predp[j]);
                        curdp1[j]=min(curdp1[j],predp[j-1]+val);
                    }
                }
            }
            swap(pre,cur);
        }
        int ans=INF;
        for(int h=0;h<8;h++)
        {
            for(int s=len;s>=0;s--)
            {
                int sta=S[s];
                int cnt=0;
                int _sta=sta^all;
                for(int i=0;i<8;i++)
                    if(_sta&(1<<i))cnt++;
                ans=min(ans,dp[pre][h][sta][V]+cnt);
            }
        }
        printf("Case %d: %d\n\n",kase++,ans);
    }
    return 0;
}