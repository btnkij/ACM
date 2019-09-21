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

const int MAXN=1e5+10;
int arr[MAXN];
struct segment_tree
{
    int n;
    int sum[MAXN<<2];
    char rw[MAXN<<2];
    char rev[MAXN<<2];
    inline int push_up(int p)
    {
        sum[p]=sum[p<<1]+sum[p<<1|1];
    }
    inline void push_down(int p, int lt, int rt)
    {
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        if(rw[p]!=-1)
        {
            sum[lc]=rw[p]*(mid-lt+1);
            sum[rc]=rw[p]*(rt-mid);
            rw[lc]=rw[rc]=rw[p];
            rev[lc]=rev[rc]=0;
            rw[p]=-1;
        }
        if(rev[p])
        {
            sum[lc]=(mid-lt+1)-sum[lc];
            sum[rc]=(rt-mid)-sum[rc];
            rev[lc]^=1, rev[rc]^=1;
            rev[p]=0;
        }
    }
    void build(int p, int lt, int rt)
    {
        rw[p]=-1, rev[p]=0;
        if(lt==rt)
        {
            sum[p]=arr[lt]&1;
            return;
        }
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        build(lc,lt,mid);
        build(rc,mid+1,rt);
        push_up(p);
    }
    void rewrite(int p, int lt, int rt, int qlt, int qrt, int qval)
    {
        if(qlt<=lt && rt<=qrt)
        {
            sum[p]=qval*(rt-lt+1);
            rw[p]=qval;
            rev[p]=0;
            return;
        }
        push_down(p, lt, rt);
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        if(qlt<=mid)rewrite(lc,lt,mid,qlt,qrt,qval);
        if(mid<qrt)rewrite(rc,mid+1,rt,qlt,qrt,qval);
        push_up(p);
    }
    void reverse(int p, int lt, int rt, int qlt, int qrt)
    {
        if(qlt<=lt && rt<=qrt)
        {
            sum[p]=(rt-lt+1)-sum[p];
            rev[p]^=1;
            return;
        }
        push_down(p, lt, rt);
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        if(qlt<=mid)reverse(lc,lt,mid,qlt,qrt);
        if(mid<qrt)reverse(rc,mid+1,rt,qlt,qrt);
        push_up(p);
    }
    int query(int p, int lt, int rt, int qlt, int qrt)
    {
        if(qlt<=lt && rt<=qrt)return sum[p];
        push_down(p, lt, rt);
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        int ans=0;
        if(qlt<=mid)ans+=query(lc,lt,mid,qlt,qrt);
        if(mid<qrt)ans+=query(rc,mid+1,rt,qlt,qrt);
        return ans;
    }
}tree[24];

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)readi(arr[i]);
    for(int i=0;i<=20;i++)
    {
        tree[i].build(1,1,n);
        rep(i,1,n)arr[i]>>=1;
    }
    int q; readi(q);
    while(q--)
    {
        int op,l,r,x; readi(op,l,r);
        ll ans;
        switch(op)
        {
        case 1: // sum
            ans=0;
            for(int i=20;i>=0;i--)
            {
                ans=(ans<<1)+tree[i].query(1,1,n,l,r);
            }
            printf("%I64d\n",ans);
            break;
        case 2: // xor
            readi(x);
            for(int i=0;i<=20;i++)
            {
                if((x&(1<<i))==0)continue;
                tree[i].reverse(1,1,n,l,r);
            }
            break;
        case 3: // or
            readi(x);
            for(int i=0;i<=20;i++)
            {
                if((x&(1<<i))==0)continue;
                tree[i].rewrite(1,1,n,l,r,1);
            }
            break;
        break;
        case 4: // and
            readi(x);
            for(int i=0;i<=20;i++)
            {
                if(x&(1<<i))continue;
                tree[i].rewrite(1,1,n,l,r,0);
            }
            break;
        }
    }
    return 0;
}