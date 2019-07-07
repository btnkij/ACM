/**
* Number:2215
* Title:oydy的征途I
* Status:AC
* Tag:[最小生成树, mst, 并查集]
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

struct Edge
{
    int from,to,dis;
    bool operator<(const Edge& rhs)const
    {
        return dis<rhs.dis;
    }
}edges[200010];
int fa[200010];
bool vis[200010];
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
    int n,m; readi(n,m);
    repne(i,0,m)readi(edges[i].from, edges[i].to, edges[i].dis);
    sort(edges,edges+m);
    int cnt=n;
    rep(i,1,n)fa[i]=i;
    ll ans1=0,ans2=0;
    int maxedge=-INF;
    repne(i,0,m)
    {
        Edge& e=edges[i];
        if(merge(e.from,e.to))
        {
            vis[i]=true;
            ans1+=e.dis;
            maxedge=max(maxedge,e.dis);
        }
    }
    ans1-=maxedge;
    rep(i,1,n)fa[i]=i;
    repne(i,0,m)
    {
        Edge& e=edges[i];
        if(vis[i] && e.dis!=maxedge)
            merge(e.from,e.to);
    }
    repne(i,0,m)
    {
        Edge& e=edges[i];
        int rx=findr(e.from),ry=findr(e.to);
        if(rx!=ry)ans2++;
    }
    printf("%lld %lld",ans1,ans2);
    return 0;
}