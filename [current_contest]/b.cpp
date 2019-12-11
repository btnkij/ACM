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

int fa[200010],rk[200010];
int findr(int x)
{
    return x==fa[x]?x:fa[x]=findr(fa[x]);
}
void merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx!=ry)fa[rx]=ry,rk[ry]+=rk[rx];
}
int a[200010],pos[200010];
char ans[200010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        rep(i,1,n)
        {
            readi(a[i]);
            pos[a[i]]=i;
            fa[i]=i, rk[i]=1;
            ans[i]='0';
        }
        rep(i,1,n)
        {
            int x=pos[i];
            if(x>1 && a[x-1]<i)merge(a[x-1],i);
            if(x<n && a[x+1]<i)merge(a[x+1],i);
            if(findr(1)==i && rk[fa[1]]==i)ans[i]='1';
        }
        ans[n+1]='\0';
        puts(ans+1);
    }
    return 0;
}