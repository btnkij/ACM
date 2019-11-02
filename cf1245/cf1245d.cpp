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

struct Edge
{
    int u,v;
    ll w;
    bool operator<(const Edge& rhs)const
    {
        return w<rhs.w;
    }
};
ll x[2010],y[2010],c[2010],k[2010];
int fa[2010];
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
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)scanf("%lld %lld",x+i,y+i);
    vector<Edge> edges;
    rep(i,1,n)
    {
        scanf("%lld",c+i);
        edges.push_back((Edge){0,i,c[i]});
    }
    rep(i,1,n)
    {
        scanf("%lld",k+i);
        repne(j,1,i)
        {
            edges.push_back(
                (Edge){i, j, (abs(x[i]-x[j])+abs(y[i]-y[j]))*(k[i]+k[j])}
            );
        }
    }
    rep(i,0,n)fa[i]=i;
    int part=n+1;
    sort(edges.begin(),edges.end());
    vector<int> plant;
    vector<Edge> route;
    ll cost=0;
    for(auto e:edges)
    {
        if(merge(e.u,e.v))
        {
            if(e.u==0 || e.v==0)plant.push_back(e.u|e.v);
            else route.push_back(e);
            cost+=e.w;
        }
    }
    printf("%lld\n",cost);
    printf("%d\n",plant.size());
    for(int x:plant)printf("%d ",x);
    puts("");
    printf("%d\n",route.size());
    for(auto e:route)printf("%d %d\n",e.u,e.v);
    return 0;
}