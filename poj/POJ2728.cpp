/**
* Number:poj2728
* Title:Desert King
* Status:AC
* Tag:[01分数规划, 最小生成树, Dinkelbach]
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

const int MAXN=1010;
struct Edge
{
    int u,v;
    double d;
    bool operator<(const Edge& rhs)const
    {
        return d<rhs.d;
    }
}edges[MAXN*MAXN];

int tot,x[MAXN],y[MAXN],z[MAXN];
double d[MAXN][MAXN],h[MAXN][MAXN];

int fa[MAXN];
int findr(int x)
{
    return x==fa[x]?x:fa[x]=findr(fa[x]);
}
bool merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx==ry)return false;
    fa[rx]=ry;
    return true;
}
double kruskal(int n,double mid)
{
    double a=0,b=0;
    rep(i,1,n)fa[i]=i;
    sort(edges,edges+tot);
    repne(i,0,tot)
    {
        Edge& e=edges[i];
        if(merge(e.u,e.v))
            a+=h[e.u][e.v],b+=d[e.u][e.v];
    }
    return a/b;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF && n)
    {
        rep(i,1,n)readi(x[i],y[i],z[i]);
        rep2(i,1,n,j,i+1,n)
        {
            d[i][j]=sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
            h[i][j]=abs(z[i]-z[j]);
        }
        double ans=0;
        while(true)
        {
            tot=0;
            rep2(i,1,n,j,i+1,n)
                edges[tot++]=(Edge){i,j,h[i][j]-ans*d[i][j]};
            double tmp=kruskal(n,ans);
            if(fabs(ans-tmp)<1e-4)break;
            ans=tmp;
        }
        printf("%.3f\n",ans);
    }
    return 0;
}