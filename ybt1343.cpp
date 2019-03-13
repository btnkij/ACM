/**
* Number:ybt1343
* Title:【例4-2】牛的旅行
* Status:AC
* Tag:[floyd, 暴力]
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

#define INF 5e100
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

double adj[200][200];
void floyd(int n)
{
    for(int i = 1; i <= n; i++)
        adj[i][i] = 0;
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[j][k]);
            }
        }
    }
}
double x[200],y[200];
double maxdis[200];
inline double dist(int i,int j)
{
    return sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)scanf("%lf %lf",&x[i],&y[i]);
    rep2(i,1,n,j,1,n)
    {
        int t; scanf("%1d",&t);
        if(t)adj[i][j]=adj[j][i]=dist(i,j);
        else adj[i][j]=adj[j][i]=INF;
    }
    floyd(n);
    double ans=INF;
    rep2(i,1,n,j,1,n)
    {
        if(adj[i][j]<INF && adj[i][j]>maxdis[i])
            maxdis[i]=adj[i][j];
    }
    rep2(i,1,n,j,1,n)
    {
        if(adj[i][j]<INF)continue;
        ans=min(ans,dist(i,j)+maxdis[i]+maxdis[j]);
    }
    rep(i,1,n)ans=max(ans,maxdis[i]);
    printf("%.6lf",ans);
    return 0;
}