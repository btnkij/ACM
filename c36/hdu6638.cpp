/**
* Number:hdu6638
* Title:Snowy Smile
* Status:AC
* Tag:[线段树, 最大子矩阵和]
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

const int MAXN=2010;
ll allmax[MAXN<<2],lmax[MAXN<<2],rmax[MAXN<<2],sum[MAXN<<2];
void pushup(int p)
{
    int lc=p<<1,rc=lc|1;
    allmax[p]=max(rmax[lc]+lmax[rc],max(allmax[lc],allmax[rc]));
    lmax[p]=max(lmax[lc],sum[lc]+lmax[rc]);
    rmax[p]=max(rmax[rc],sum[rc]+rmax[lc]);
    sum[p]=sum[lc]+sum[rc];
}
void build(int p,int l,int r)
{
    if(l==r)
    {
        allmax[p]=lmax[p]=rmax[p]=sum[p]=0;
        return;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    pushup(p);
}
void update(int p,int l,int r,int qpos,int qval)
{
    if(l==r)
    {
        allmax[p]+=qval, lmax[p]+=qval, rmax[p]+=qval, sum[p]+=qval;
        return;
    }
    int mid=(l+r)>>1;
    if(qpos<=mid)update(p<<1,l,mid,qpos,qval);
    else update(p<<1|1,mid+1,r,qpos,qval);
    pushup(p);
}
inline ll query()
{
    return allmax[1];
}

struct Node
{
    int x,y,w;
    bool operator<(const Node& rhs)const
    {
        return x<rhs.x;
    }
}nodes[MAXN];
int y[MAXN];

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
            Node& nod=nodes[i];
            readi(nod.x,nod.y,nod.w);
            y[i]=nod.y;
        }
        sort(y+1,y+n+1);
        int toty=unique(y+1,y+n+1)-y;
        rep(i,1,n)
        {
            Node& nod=nodes[i];
            nod.y=lower_bound(y+1,y+toty,nod.y)-y;
        }
        sort(nodes+1,nodes+n+1);
        int pre=1;
        ll ans=0;
        while(pre<=n)
        {
            build(1,1,n);
            int i=pre;
            while(i==pre || nodes[i].x==nodes[i-1].x)
            {
                update(1,1,n,nodes[i].y,nodes[i].w);
                i++;
            }
            pre=i;
            int j=i;
            ans=max(ans,query());
            int prej=j;
            while(j<=n)
            {
                while(j<=n && (j==prej || nodes[j].x==nodes[j-1].x))
                {
                    update(1,1,n,nodes[j].y,nodes[j].w);
                    j++;
                }
                prej=j;
                ans=max(ans,query());
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}