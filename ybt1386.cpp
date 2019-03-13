/**
* Number:ybt1386
* Title:打击犯罪(black)
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

const int MAXN=1010;
int fa[MAXN],rk[MAXN];
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
int maxrk;
bool merge(int x,int y)
{
    int rx=find(x),ry=find(y);
    if(rx==ry)return false;
    fa[rx]=ry;
    rk[ry]+=rk[rx];
    maxrk=max(maxrk,rk[ry]);
    return true;
}

int arr[MAXN][MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)
    {
        fa[i]=i;
        rk[i]=1;
        int m; readi(m);
        arr[i][0]=m;
        rep(j,1,m)readi(arr[i][j]);
    }
    maxrk=0;
    int i;
    for(i=n;i>=1;i--)
    {
        int m=arr[i][0];
        rep(j,1,m)if(arr[i][j]>=i)merge(i,arr[i][j]);
        if(maxrk>(n>>1))break;
    }
    printf("%d",i);
    return 0;
}