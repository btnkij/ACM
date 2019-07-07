/**
* Number:
* Title:
* Status:WA
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

const int MAXN = 100010<<2;
const ll MOD = 1e9+7;
ll sum[MAXN];
ll sum2[MAXN];
ll add[MAXN], mul[MAXN], chg[MAXN];
void pushup(int p)
{
    int lc=p<<1, rc=lc|1;
    sum[p]=(sum[lc]+sum[rc])%MOD;
    sum2[p]=(sum2[lc]+sum2[rc])%MOD;
}
void build(int p, int lt, int rt)
{
    if(lt>rt)return;
    if(lt == rt)
    {
        scanf("%lld", &sum[p]);
        sum2[p]=(sum[p]*sum[p])%MOD;
        pushup(p);
        return;
    }
    int mid = (lt + rt) >> 1;
    build(p<<1,lt,mid);
    build(p<<1|1,mid+1,rt);
    pushup(p);
}
void pushdown(int p,int lt,int rt)
{
    int mid=(lt+rt)>>1;
    int llen=mid-lt+1, rlen=rt-mid;
    int lc=p<<1, rc=lc|1;
    if(chg[p]!=-1)
    {
        sum[lc]=chg[p]*llen%MOD;
        sum2[lc]=sum[lc]*chg[p]%MOD;
        sum[rc]=chg[p]*rlen%MOD;
        sum2[rc]=sum[rc]*chg[p]%MOD;
        chg[lc]=chg[rc]=chg[p];
        mul[lc]=mul[rc]=1;
        add[lc]=add[rc]=0;
        chg[p]=-1;
    }
    if(mul[p]!=1)
    {
        sum[lc]=sum[lc]*mul[p]%MOD;
        sum2[lc]=sum2[lc]*mul[p]*mul[p]%MOD;
        sum[rc]=sum[rc]*mul[p]%MOD;
        sum2[rc]=sum2[rc]*mul[p]*mul[p]%MOD;
        mul[lc]=mul[lc]*mul[p]%MOD, mul[rc]=mul[rc]*mul[p]%MOD;
        add[lc]=add[lc]*mul[p]%MOD, add[rc]=add[rc]*mul[p]%MOD;
        mul[p]=1;
    }
    if(add[p]!=0)
    {
        sum2[lc]=(sum2[lc]+add[p]*add[p]*llen%MOD+2*llen*sum[lc]%MOD)%MOD;
        sum[lc]=(sum[lc]+add[p]*llen)%MOD;
        sum2[rc]=(sum2[rc]+add[p]*add[p]*rlen%MOD+2*rlen*sum[rc]%MOD)%MOD;
        sum[rc]=(sum[rc]+add[p])%MOD;
        add[lc]=(add[lc]+add[p])%MOD, add[rc]=(add[rc]+add[p])%MOD;
        add[p]=0;
    }
}
void update1(int p,int lt,int rt,int ql,int qr,ll val)
{
    int lc=p<<1, rc=lc|1;
    int len=rt-lt+1;
    if(ql<=lt && rt<=qr)
    {
        sum2[p]=(sum2[p]+val*val*len%MOD+2*len*sum[p]%MOD)%MOD;
        sum[p]=(sum[p]+val*len)%MOD;
        add[p]=(add[p]+val)%MOD;
        return;
    }
    pushdown(p,lt,rt);
    int mid=(lt+rt)>>1;
    if(ql<=mid)update1(lc,lt,mid,ql,qr,val);
    if(mid<qr)update1(rc,mid+1,rt,ql,qr,val);
    pushup(p);
}
void update2(int p,int lt,int rt,int ql,int qr,ll val)
{
    int lc=p<<1, rc=lc|1;
    int len=rt-lt+1;
    if(ql<=lt && rt<=qr)
    {
        sum[p]=sum[p]*val%MOD;
        sum2[p]=sum2[p]*val*val%MOD;
        mul[p]=mul[p]*val%MOD;
        add[p]=add[p]*val%MOD;
        return;
    }
    pushdown(p,lt,rt);
    int mid=(lt+rt)>>1;
    if(ql<=mid)update2(lc,lt,mid,ql,qr,val);
    if(mid<qr)update2(rc,mid+1,rt,ql,qr,val);
    pushup(p);
}
void update3(int p,int lt,int rt,int ql,int qr,ll val)
{
    int lc=p<<1, rc=lc|1;
    int len=rt-lt+1;
    if(ql<=lt && rt<=qr)
    {
        sum[p]=val*len%MOD;
        sum2[p]=sum[p]*val%MOD;
        chg[p]=val;
        mul[p]=1;
        add[p]=0;
        return;
    }
    pushdown(p,lt,rt);
    int mid=(lt+rt)>>1;
    if(ql<=mid)update3(lc,lt,mid,ql,qr,val);
    if(mid<qr)update3(rc,mid+1,rt,ql,qr,val);
    pushup(p);
}
ll query_sum(int p,int lt,int rt,int ql,int qr)
{
    if(ql<=lt && rt<=qr)
    {
        return sum[p];
    }
    pushdown(p,lt,rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    ll ans=0;
    if(ql<=mid)ans=(ans+query_sum(lc,lt,mid,ql,qr))%MOD;
    if(mid<qr)ans=(ans+query_sum(rc,mid+1,rt,ql,qr))%MOD;
    return ans;
}
ll query_sum2(int p,int lt,int rt,int ql,int qr)
{
    if(ql<=lt && rt<=qr)
    {
        return sum2[p];
    }
    pushdown(p,lt,rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    ll ans=0;
    if(ql<=mid)ans=(ans+query_sum2(lc,lt,mid,ql,qr))%MOD;
    if(mid<qr)ans=(ans+query_sum2(rc,mid+1,rt,ql,qr))%MOD;
    return ans;
}
void show(int n)
{
    printf("\nsum:\n");
    for(int i=1;i<=(n<<2);i++)printf("%lld ",sum[i]);
    printf("\nsum2:\n");
    for(int i=1;i<=(n<<2);i++)printf("%lld ",sum2[i]);
    printf("\n");
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, q;
    readi(n, q);
    fill(mul, mul+(n<<2)+10, 1);
    fill(chg, chg+(n<<2)+10, -1);
    build(1,1,n);
    // show(n);
    while(q--)
    {
        int op,L,R; readi(op,L,R);
        ll k;
        switch(op)
        {
            case 1:
            scanf("%lld",&k);
            update1(1,1,n,L,R,k);
            // show(n);
            break;
            case 2:
            scanf("%lld",&k);
            update2(1,1,n,L,R,k);
            // show(n);
            break;
            case 3:
            scanf("%lld",&k);
            update3(1,1,n,L,R,k);
            // show(n);
            break;
            case 4:
            ll s=query_sum(1,1,n,L,R);
            ll s2=query_sum2(1,1,n,L,R);
            ll ans=(((R-L+1)*s2%MOD-s*s%MOD)%MOD+MOD)%MOD;
            printf("%lld\n",ans);
            break;
        }
    }
    return 0;
}