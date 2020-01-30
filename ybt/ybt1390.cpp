/**
* Number:ybt1390
* Title:食物链【NOI2001】
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

const int MAXN=50010;
int fa[MAXN],rel[MAXN];
int find(int x)
{
    if(x==fa[x])return x;
    int rx=find(fa[x]);
    rel[x]=(rel[x]+rel[fa[x]])%3;
    fa[x]=rx;
    return rx;
}
bool merge(int x,int y,int p)
{
    int rx=find(x),ry=find(y);
    if(rx==ry)return rel[x]==(p+rel[y])%3;
    fa[rx]=ry;
    rel[rx]=(rel[y]+p-rel[x]+3)%3;
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k; readi(n,k);
    rep(i,1,n)fa[i]=i;
    int d,x,y;
    int ans=0;
    while(k--)
    {
        readi(d,x,y);
        d--;
        if(x>n || y>n || !merge(x,y,d))
            ans++;
    }
    printf("%d",ans);
    return 0;
}