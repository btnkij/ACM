/**
* Number:ybt1387
* Title:搭配购买(buy)
* Status:AC
* Tag:[并查集, 01背包]
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

const int MAXN=10010;
int dp[MAXN];

int fa[MAXN],w[MAXN],v[MAXN];
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
bool merge(int x,int y)
{
    int rx=find(x),ry=find(y);
    if(rx==ry)return false;
    fa[rx]=ry;
    w[ry]+=w[rx];
    v[ry]+=v[rx];
    return true;
}

bool vis[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,V; readi(n,m,V);
    rep(i,1,n)
    {
        fa[i]=i;
        readi(w[i],v[i]);
    }
    while(m--)
    {
        int u,v; readi(u,v);
        merge(u,v);
    }
    rep(i,1,n)vis[find(i)]=true;
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])continue;
        for(int j=V;j>=w[i];j--)
        {
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    printf("%d",dp[V]);
    return 0;
}