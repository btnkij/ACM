/**
* Number:2177
* Title:神
* Status:AC
* Tag:[dp]
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

int dp[1010][30];
bool vis[1010][30];
int cnt[1010];
char s[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int k; readi(k);
        reads(s);
        int len=strlen(s);
        int n=len/k;
        mset(dp,INF);
        mset(vis,false);
        mset(cnt,0);
        for(int i=0;i<n;i++)
        {
            int lt=i*k, rt=(i+1)*k;
            for(int j=lt;j<rt;j++)
            {
                char ch=s[j]-'a';
                if(!vis[i][ch])
                {
                    vis[i][ch]=true;
                    cnt[i]++;
                }
            }
        }
        for(int j=0;j<26;j++)
            if(vis[0][j])dp[0][j]=cnt[0];
        for(int i=1;i<n;i++)
        {
            for(int head=0;head<26;head++)
            {
                if(vis[i-1][head])
                {
                    if(vis[i][head])
                    {
                        for(int tail=0;tail<26;tail++)
                            if(vis[i][tail] && head!=tail)
                                dp[i][tail]=min(dp[i][tail],dp[i-1][head]+cnt[i]-1);
                        if(cnt[i]==1)
                            dp[i][head]=min(dp[i][head],dp[i-1][head]);
                    }
                    else
                    {
                        for(int tail=0;tail<26;tail++)
                            if(vis[i][tail])
                                dp[i][tail]=min(dp[i][tail],dp[i-1][head]+cnt[i]);
                    }
                }
            }
        }
        int ans=INF;
        for(int i=0;i<26;i++)
            ans=min(ans,dp[n-1][i]);
        printf("%d\n",ans);
    }
    return 0;
}