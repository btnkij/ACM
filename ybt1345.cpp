/**
* Number:ybt1345
* Title:【例4-6】香甜的黄油
* Status:AC
* Tag:[floyd]
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

int adj[810][810];
int cow[810];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,p,c; readi3(n,p,c);
    repne(i,0,n)
    {
        int t; readi(t);
        cow[t]++;
    }
    mset(adj,INF);
    rep(i,1,p)adj[i][i]=0;
    repne(i,0,c)
    {
        int a,b,d; readi3(a,b,d);
        adj[a][b]=adj[b][a]=d;
    }
    rep(k,1,p)
    {
        rep2(i,1,p,j,1,i)
        {
            if(adj[i][k]+adj[k][j]<adj[i][j])
                adj[j][i]=adj[i][j]=adj[i][k]+adj[k][j];
        }
    }
    int ans=INF;
    rep(i,1,p)
    {
        int sum=0;
        rep(j,1,p)
        {
            sum+=cow[j]*adj[i][j];
        }
        ans=min(ans,sum);
    }
    printf("%d",ans);
    return 0;
}