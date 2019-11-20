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

int fa[200010],maxson[200010];
int findr(int x)
{
    return x==fa[x]?x:fa[x]=findr(fa[x]);
}
int merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx==ry)return 0;
    if(rx>ry)swap(rx,ry);
    fa[ry]=rx;
    maxson[rx]=max(maxson[rx],maxson[ry]);
    return 1;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)fa[i]=maxson[i]=i;
    rep(i,1,m)
    {
        int u,v; readi(u,v);
        merge(u,v);
    }
    int ans=0,cur=1;
    while(cur<=n)
    {
        int i=cur+1;
        while(i<=maxson[cur])
        {
            ans+=merge(cur,i);
            i++;
        }
        cur=i;
    }
    printf("%d\n",ans);
    return 0;
}