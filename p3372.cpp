#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN=1e5+10;
struct segment_tree
{
    int n;
    ll sum[MAXN<<2];
    ll lazy[MAXN<<2];
    inline ll push_up(ll lhs, ll rhs)
    {
        return lhs+rhs;
    }
    inline void push_down(int p, int lt, int rt)
    {
        if(lazy[p])
        {
            int lc=p<<1, rc=lc|1;
            int mid=(lt+rt)>>1;
            sum[lc]=push_up(sum[lc],lazy[p]*(mid-lt+1));
            sum[rc]=push_up(sum[rc],lazy[p]*(rt-mid));
            lazy[lc]+=lazy[p];
            lazy[rc]+=lazy[p];
            lazy[p]=0;
        }
    }
    void build_help(int p, int lt, int rt)
    {
        if(lt==rt)
        {
            scanf("%lld",&sum[p]);
            return;
        }
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        build_help(lc,lt,mid);
        build_help(rc,mid+1,rt);
        sum[p]=push_up(sum[lc],sum[rc]);
    }
    void build(int n)
    {
        this->n=n;
        build_help(1,1,n);
    }
    int qlt,qrt;
    ll qval;
    void add_help(int p, int lt, int rt)
    {
        if(qlt<=lt && rt<=qrt)
        {
            sum[p]=push_up(sum[p],qval*(rt-lt+1));
            lazy[p]+=qval;
            return;
        }
        push_down(p, lt, rt);
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        if(qlt<=mid)add_help(lc,lt,mid);
        if(mid<qrt)add_help(rc,mid+1,rt);
        sum[p]=push_up(sum[lc], sum[rc]);
    }
    void add(int qlt, int qrt, ll delta)
    {
        this->qlt=qlt, this->qrt=qrt;
        this->qval=delta;
        add_help(1,1,n);
    }
    ll query_help(int p, int lt, int rt)
    {
        if(qlt<=lt && rt<=qrt)return sum[p];
        push_down(p, lt, rt);
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        bool nul=true;
        ll ans;
        if(qlt<=mid)
        {
            ans=query_help(lc,lt,mid);
            nul=false;
        }
        if(mid<qrt)
        {
            if(nul)ans=query_help(rc,mid+1,rt);
            else ans=push_up(ans,query_help(rc,mid+1,rt));
        }
        return ans;
    }
    ll query(int qlt, int qrt)
    {
        this->qlt=qlt, this->qrt=qrt;
        return query_help(1,1,n);
    }
}segtree;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int n,m; scanf("%d %d",&n,&m);
    segtree.build(n);
    while(m--)
    {
        int op,x,y;
        scanf("%d %d %d",&op,&x,&y);
        if(op==1)
        {
            ll k; scanf("%lld",&k);
            segtree.add(x,y,k);
        }
        else if(op==2)
        {
            printf("%lld\n",segtree.query(x,y));
        }
    }
    return 0;
}