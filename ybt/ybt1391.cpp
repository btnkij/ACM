/**
* Number:ybt1391
* Title:局域网(net)
* Status:AC
* Tag:[kruskal]
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

int fa[110];
int find(int x)
{
    return x==fa[x] ? x : fa[x]=find(fa[x]);
}
bool merge(int x,int y)
{
    int rx=find(x), ry=find(y);
    if(rx==ry)return false;
    fa[rx]=ry;
    return true;
}

struct Edge
{
    int u,v,d;
    bool operator<(const Edge& rhs)const
    {
        return d < rhs.d;
    }
}edges[110*110];

int n,e;
int kruskal()
{
    int cnt=1,ans=0;
    sort(edges,edges+e);
    rep(i,1,n)fa[i]=i;
    repne(i,0,e)
    {
        if(merge(edges[i].u, edges[i].v))
        {
            cnt++;
            ans+=edges[i].d;
            if(cnt==n)return ans;
        }
    }
    return -1;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,e);
    int sum=0;
    repne(i,0,e)
    {
        Edge& ed=edges[i];
        readi(ed.u,ed.v,ed.d);
        sum+=ed.d;
    }
    int ans=kruskal();
    printf("%d",sum-ans);
    return 0;
}