/**
* Number:2220
* Title:hqf吹泡泡
* Status:AC
* Tag:[最小生成树, mst]
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
    int u,v,w;
    bool operator<(const Edge& rhs)const
    {
        return w<rhs.w;
    }
}edges[500010];

int fa[1010];
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

int kruskal(int n,int m,int k)
{
    rep(i,1,n)fa[i]=i;
    int cnt=n;
    sort(edges,edges+m);
    int ans=0;
    for(int i=0;i<m&&cnt>k;i++)
    {
        Edge& e=edges[i];
        if(merge(e.u,e.v))
        {
            cnt--;
            ans+=e.w;
        }
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,k; readi(n,m,k);
    repne(i,0,m)readi(edges[i].u,edges[i].v,edges[i].w);
    printf("%d",kruskal(n,m,k));
    return 0;
}