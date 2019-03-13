/**
* Number:ybt1385
* Title:团伙(group)
* Status:?
* Tag:[]
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
int fa[MAXN*2];
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    int rx=find(x),ry=find(y);
    if(rx!=ry)fa[rx]=ry;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n<<1)fa[i]=i;
    while(m--)
    {
        int p,a,b; readi(p,a,b);
        if(p==0)
        {
            merge(a,b);
        }
        else if(p==1)
        {
            merge(a+n,b);
            merge(b+n,a);
        }
    }
    int cnt=0;
    rep(i,1,n)
    {
        if(i==find(i))cnt++;
    }
    printf("%d",cnt);
    return 0;
}

/*
//WA 敌人的朋友的敌人不是朋友
const int MAXN=1010;
int fa[MAXN],rel[MAXN];
int find(int x)
{
    if(x==fa[x])return x;
    int rx=find(fa[x]);
    rel[x]=(rel[x]^rel[fa[x]]);
    fa[x]=rx;
    return rx;
}
void merge(int x,int y,int p)
{
    int rx=find(x),ry=find(y);
    if(rx==ry)return;
    fa[rx]=ry;
    rel[rx]=(p^rel[x]^rel[y]);
}

bool vis[MAXN][2];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)fa[i]=i;
    while(m--)
    {
        int p,a,b; readi(p,a,b);
        merge(a,b,p);
    }
    int cnt=0;
    rep(i,1,n)
    {
        int r=find(i);
        // printf("%d %d %d\n",i,r,rel[i]);
        if(!vis[r][rel[i]])
        {
            printf("%d %d\n",r,rel[i]);
            cnt++;
        }
        vis[r][rel[i]]=true;
    }
    printf("%d",cnt);
    return 0;
}
*/