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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int fa[100010];
int getfa(int x)
{
    return x==fa[x] ? x : fa[x]=getfa(fa[x]);
}
bool merge(int x,int y)
{
    int rx=getfa(x),ry=getfa(y);
    if(rx==ry)return false;
    fa[rx]=ry;
    return true;
}

int a[100010],b[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m,n; readi(m,n);
    rep(i,1,m)fa[i]=i;
    rep(i,1,m)
    {
        int k; readi(k);
        rep(j,1,k)
        {
            int ci; readi(ci);
            if(a[ci]==0)a[ci]=i;
            else b[ci]=i;
        }
    }
    int ans=0;
    rep(i,1,n)
    {
        if(merge(a[i],b[i]))ans++;
    }
    printf("%d",ans);
    return 0;
}