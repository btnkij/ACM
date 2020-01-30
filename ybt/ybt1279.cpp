/**
* Number:ybt1279
* Title:橱窗布置(flower)
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int cost[104][104];
int dp[104][104],pre[104][104];
void showpath(int f,int idx)
{
    if(f==0)return;
    showpath(f-1,pre[f][idx]);
    printf("%d ",idx);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int f,v;
    readi2(f,v);
    rep2(i,1,f,j,1,v)readi(cost[i][j]);
    rep2(i,1,f,j,1,v)
    {
        int tmp=-INF;
        repne(k,i-1,j)
        {
            if(tmp<dp[i-1][k])
            {
                tmp=dp[i-1][k];
                pre[i][j]=k;
            }
        }
        dp[i][j]=tmp+cost[i][j];
    }
    int idx,ans=-INF;
    rep(i,f,v)
    {
        if(dp[f][i]>ans)
        {
            ans=dp[f][i];
            idx=i;
        }
    }
    printf("%d\n",dp[f][idx]);
    showpath(f,idx);
    return 0;
}