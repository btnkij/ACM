/**
* Number:scu4441
* Title:Necklace
* Status:AC
* Tag:[dp, 线段树]
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

int a[200010];
int l[200010],r[200010];
int n;

int tree[10010<<2];
void build(int p,int lt,int rt)
{
    memset(tree,0,sizeof(tree));
}
int query(int p,int lt,int rt,int qlt,int qrt)
{
    if(rt<qlt || lt>qrt)return 0;
    if(qlt<=lt && rt<=qrt)return tree[p];
    int mid=(lt+rt)>>1;
    int lef=query(p<<1,lt,mid,qlt,qrt);
    int rig=query(p<<1|1,mid+1,rt,qlt,qrt);
    return max(lef,rig);
}
void update(int p,int lt,int rt, int pos, int val)
{
    if(lt==rt)
    {
        tree[p]=max(tree[p], val);
        return;
    }
    int mid=(lt+rt)>>1;
    if(pos<=mid)update(p<<1,lt,mid,pos,val);
    else update(p<<1|1,mid+1,rt,pos,val);
    tree[p]=max(tree[p<<1],tree[p<<1|1]);
}

int solve(int p)
{
    mset(l,0);
    mset(r,0);
    int liml=min(n-1,p-1);
    build(1,1,9999);
    for(int i=1;i<=liml;i++)
    {
        if(a[p-i]==10000)continue;
        l[i]=a[p-i]+query(1,1,9999,a[p-i],9999);
        update(1,1,9999,a[p-i],l[i]);
        l[i]=max(l[i-1], l[i]);
    }
    int limr=min(n-1,2*n-p);
    build(1,1,9999);
    for(int i=1;i<=limr;i++)
    {
        if(a[p+i]==10000)continue;
        r[i]=a[p+i]+query(1,1,9999,a[p+i],9999);
        update(1,1,9999,a[p+i],r[i]);
        r[i]=max(r[i-1], r[i]);
    }
    // rep(i,1,liml)printf("%d ",l[i]);
    // printf("\n");
    // rep(i,1,limr)printf("%d ",r[i]);
    // printf("\n");
    int ans=0;
    for(int i=liml;i>=0;i--)
    {
        int j=n-1-i;
        if(!(0<=j && j<=limr))continue;
        ans=max(l[i]+r[j], ans);
        // if(ans==13)printf("%d %d\n",i,j);
    }
    ans+=10000;
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n)!=EOF)
    {
        rep(i,1,n)readi(a[i]);
        copy(a+1,a+n+1,a+n+1);
        int ub=n*2;
        int ans=0;
        rep(i,1,ub)
        {
            if(a[i]==10000)
            {
                ans=max(ans,solve(i));
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}