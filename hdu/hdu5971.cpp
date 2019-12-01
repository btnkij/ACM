/**
* Number:hdu5971
* Title:Wrestling Match
* Status:AC
* Tag:[并查集]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int fa[1010], rel[1010];
int findr(int x)
{
    if(x==fa[x])return x;
    int rx=findr(fa[x]);
    rel[x]=rel[fa[x]]^rel[x];
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
bool vis[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,x,y;
    while(readi(n,m,x,y)!=EOF)
    {
        rep(i,1,n)
        {
            fa[i]=i;
            rel[i]=0;
            vis[i]=false;
        }
        bool ok=true;
        repne(i,0,m)
        {
            int a,b; readi(a,b);
            vis[a]=vis[b]=true;
            if(ok)ok=merge(a,b,1);
        }
        merge(n+1,n+2,1);
        repne(i,0,x)
        {
            int a; readi(a);
            vis[a]=true;
            if(ok)ok=merge(n+1,a,0);
        }
        repne(i,0,y)
        {
            int b; readi(b);
            vis[b]=true;
            if(ok)ok=merge(n+2,b,0);
        }
        rep(i,1,n)ok=ok&&vis[i];
        printf("%s\n",ok?"YES":"NO");
    }
    return 0;
}