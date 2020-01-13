/**
* Number:poj1015
* Title:Jury Compromise
* Status:?
* Tag:[dp]
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

const int base=450;
int dp[30][900],pre[30][900];
int p[210],d[210];
vector<int> ans;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,kase=1;
    while(readi(n,m)!=EOF && n && m)
    {
        clr(dp,-1);
        clr(pre,0);
        dp[0][base]=0;
        rep(i,1,n)readi(p[i],d[i]);
        rep(i,1,n)
        {
            int diff=p[i]-d[i],sum=p[i]+d[i];
            rep(j,base-400-diff,base+400-diff)
            {
                rep(k,1,m)
                {
                    if(dp[k-1][j]==-1)continue;
                    if(dp[k-1][j]+sum>dp[k][j+diff])
                    {
                        dp[k][j+diff]=dp[k-1][j]+sum;
                        pre[k][j+diff]=i;
                    }
                }
            }
        }
        int tmp1=-INF,tmp2=-INF;
        rep(i,base-400,base+400)
        {
            if(dp[m][i]==-1)continue;
            if(abs(base-i)<abs(base-tmp1) || abs(base-i)==abs(base-tmp1) && dp[m][i]>tmp2)
            {
                tmp1=i;
                tmp2=dp[m][i];
            }
        }
        ans.clear();
        int s1=0,s2=0;
        for(int i=m;i>=1;i--)
        {
            int k=pre[i][tmp1];
            ans.push_back(k);
            tmp1-=p[k]-d[k];
            s1+=p[k],s2+=d[k];
        }
        printf("Jury #%d\n",kase++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n",s1,s2);
        for(int i=ans.size()-1;i>=0;i--)
        {
            printf("%d%c",ans[i],i?' ':'\n');
        }
        puts("");
    }
    return 0;
}