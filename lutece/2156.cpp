/**
* Number:2156
* Title:数理统计
* Status:AC
* Tag:[线段树]
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

#define INF 0x3f3f3f3f3f3f3f3f
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

const int MAXN=1000010<<2;
ll sum[MAXN],mmax[MAXN],mmin[MAXN],add[MAXN];
void maintain(int p,int lt,int rt,ll lazy)
{
    sum[p]+=lazy*(rt-lt+1);
    mmax[p]+=lazy;
    mmin[p]+=lazy;
    add[p]+=lazy;
}
void pushup(int p)
{
    sum[p]=sum[p<<1]+sum[p<<1|1];
    mmax[p]=max(mmax[p<<1],mmax[p<<1|1]);
    mmin[p]=min(mmin[p<<1],mmin[p<<1|1]);
}
void pushdown(int p,int lt,int rt)
{
    if(add[p]==0)return;
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    maintain(lc,lt,mid,add[p]);
    maintain(rc,mid+1,rt,add[p]);
    add[p]=0;
}
void build(int p,int lt,int rt)
{
    if(lt==rt)
    {
        sum[p]=add[p]=mmax[p]=mmin[p]=0;
        return;
    }
    build(p<<1,lt,(lt+rt)>>1);
    build(p<<1|1,((lt+rt)>>1)+1,rt);
    pushup(p);
}
void update(int p,int lt,int rt,int ql,int qr,ll val)
{
    if(ql<=lt && rt<=qr)
    {
        maintain(p,lt,rt,val);
        return;
    }
    pushdown(p,lt,rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(ql<=mid)update(lc,lt,mid,ql,qr,val);
    if(mid<qr)update(rc,mid+1,rt,ql,qr,val);
    pushup(p);
}
ll querysum(int p,int lt,int rt,int ql,int qr)
{
    if(ql<=lt && rt<=qr)return sum[p];
    pushdown(p,lt,rt);
    ll ans=0;
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(ql<=mid)ans+=querysum(lc,lt,mid,ql,qr);
    if(mid<qr)ans+=querysum(rc,mid+1,rt,ql,qr);
    return ans;
}
ll querymax(int p,int lt,int rt,int ql,int qr)
{
    if(ql<=lt && rt<=qr)return mmax[p];
    pushdown(p,lt,rt);
    ll ans=-INF;
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(ql<=mid)ans=max(ans,querymax(lc,lt,mid,ql,qr));
    if(mid<qr)ans=max(ans,querymax(rc,mid+1,rt,ql,qr));
    return ans;
}
ll querymin(int p,int lt,int rt,int ql,int qr)
{
    if(ql<=lt && rt<=qr)return mmin[p];
    pushdown(p,lt,rt);
    ll ans=INF;
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(ql<=mid)ans=min(ans,querymin(lc,lt,mid,ql,qr));
    if(mid<qr)ans=min(ans,querymin(rc,mid+1,rt,ql,qr));
    return ans;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,q; readi(n,q);
    mset(mmax,-INF);
    mset(mmin,INF);
    build(1,1,n);
    while(q--)
    {
        int op; readi(op);
        int L,R,k; 
        switch(op)
        {
            case 1:
            readi(L,R,k);
            update(1,1,n,L,R,k);
            break;
            case 2:
            readi(L,R);
            printf("%lld\n",querysum(1,1,n,L,R));
            break;
            case 3:
            readi(L,R);
            printf("%lld\n",querymax(1,1,n,L,R)-querymin(1,1,n,L,R));
            break;
        }
    }
    return 0;
}