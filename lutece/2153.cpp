/**
* Number:2153
* Title:对答案
* Status:AC
* Tag:[带权并查集]
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

int fa[1000010];
int rel[1000010];
int findr(int x)
{
    if(x==fa[x])return x;
    int rx=findr(fa[x]);
    rel[x]=rel[x]^rel[fa[x]];
    return fa[x]=rx;
}
bool merge(int x,int y,int r)
{
    int rx=findr(x), ry=findr(y);
    if(rx==ry)return (rel[x]^rel[y])==r;
    fa[rx]=ry;
    rel[rx]=rel[x]^rel[y]^r;
    return true;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,1,n)fa[i]=i;
    int k=0;
    for(;k<m;k++)
    {
        int u,v; readi(u,v);
        char parity[8]; scanf("%s",parity);
        if(!(parity[0]=='e' && merge(u-1,v,0) || parity[0]=='o' && merge(u-1,v,1)))
        {
            break;
        }
    }
    if(k==m)printf("ORZQHQH\n");
    else printf("%d\n",k);
    return 0;
}