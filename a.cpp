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

struct Node
{
    int lt, rt;
    int llen,rlen,lh,rh;
}dp[1010][1010];
int fro[1010],bac[1010];
char s[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(scanf("%d\n",&n)!=EOF && n)
    {
        int lb=1,rb=(n<<1)-1;
        int ans=0;
        rep(i,1,n)
        {
            fgets(s+1,sizeof(s)-1,stdin);
            dp[i][lb-1].lt=dp[i][rb+1].rt=0;
            for(int j=lb;j<=rb;j++)dp[i][j].lt=s[j]=='O'?dp[i][j-1].lt+1:0;
            for(int j=rb;j>=lb;j--)dp[i][j].rt=s[j]=='O'?dp[i][j+1].rt+1:0;
            for(int j=lb;j<=rb;j++)
            {
                if(dp[i-1][j].llen > 1)
                {
                    dp[i][j].llen = min(dp[i][j].lt, dp[i-1][j].llen-1);
                    dp[i][j].lh = dp[i-1][j].lh+1;
                }
                else if(dp[i-1][j].lt > 1)
                {
                    dp[i][j].llen = min(dp[i-1][j].lt-1, dp[i][j].lt);
                    dp[i][j].lh=2;
                }
                else
                {
                    dp[i][j].llen=dp[i][j].lt;
                    dp[i][j].lh=1;
                }

                if(dp[i-1][j].rlen > 1)
                {
                    dp[i][j].rlen = min(dp[i][j].rt, dp[i-1][j].rlen-1);
                    dp[i][j].rh = dp[i-1][j].rh+1;
                }
                else if(dp[i-1][j].rt > 1)
                {
                    dp[i][j].rlen = min(dp[i-1][j].rt-1, dp[i][j].rt);
                    dp[i][j].rh=2;
                }
                else
                {
                    dp[i][j].rlen=dp[i][j].rt;
                    dp[i][j].rh=1;
                }

                int h=min(dp[i][j].lh, dp[i][j].rh);
                ans = max(ans, h*h);
                ans = max(ans, dp[i][j].lh * dp[i][j].lh / 2);
                ans = max(ans, dp[i][j].rh * dp[i][j].rh / 2);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}