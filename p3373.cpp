#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
struct Node
{
    ll sum,add,mul;
}nodes[100010<<2];
int n,m;
ll mod;
inline void push_up(int p)
{
    nodes[p].sum=(nodes[p<<1].sum+nodes[p<<1|1].sum)%mod;
}
void push_down(int p,int lt,int rt)
{
    if(nodes[p].mul!=1 || nodes[p].add)
    {
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        if(nodes[p].mul!=1)
        {
            nodes[lc].sum=nodes[lc].sum*nodes[p].mul%mod;
            nodes[rc].sum=nodes[rc].sum*nodes[p].mul%mod;
            nodes[lc].mul=(nodes[lc].mul*nodes[p].mul)%mod;
            nodes[rc].mul=(nodes[rc].mul*nodes[p].mul)%mod;
            nodes[lc].add=(nodes[lc].add*nodes[p].mul)%mod;
            nodes[rc].add=(nodes[rc].add*nodes[p].mul)%mod;
            nodes[p].mul=1;
        }
        if(nodes[p].add)
        {
            nodes[lc].sum=(nodes[lc].sum+nodes[p].add*(mid-lt+1))%mod;
            nodes[rc].sum=(nodes[rc].sum+nodes[p].add*(rt-mid))%mod;
            nodes[lc].add=(nodes[lc].add+nodes[p].add)%mod;
            nodes[rc].add=(nodes[rc].add+nodes[p].add)%mod;
            nodes[p].add=0;
        }
    }
}
void build(int p,int lt,int rt)
{
    if(lt==rt)
    {
        scanf("%lld",&nodes[p].sum);
        return;
    }
    nodes[p].mul=1;
    int mid=(lt+rt)>>1;
    build(p<<1,lt,mid);
    build(p<<1|1,mid+1,rt);
    push_up(p);
}
int ql,qr;
ll qval;
void add_help(int p,int lt,int rt)
{
    if(ql<=lt && rt<=qr)
    {
        nodes[p].sum=(nodes[p].sum+qval*(rt-lt+1))%mod;
        nodes[p].add=(nodes[p].add+qval)%mod;
        return;
    }
    push_down(p,lt,rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(ql<=mid)add_help(lc,lt,mid);
    if(mid<qr)add_help(rc,mid+1,rt);
    push_up(p);
}
void add(int lt,int rt,ll val)
{
    ql=lt, qr=rt, qval=val%mod;
    add_help(1,1,n);
}
void multiply_help(int p,int lt,int rt)
{
    if(ql<=lt && rt<=qr)
    {
        nodes[p].sum=nodes[p].sum*qval%mod;
        nodes[p].mul=nodes[p].mul*qval%mod;
        nodes[p].add=nodes[p].add*qval%mod;
        return;
    }
    push_down(p,lt,rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(ql<=mid)multiply_help(lc,lt,mid);
    if(mid<qr)multiply_help(rc,mid+1,rt);
    push_up(p);
}
void multiply(int lt,int rt,ll val)
{
    ql=lt, qr=rt, qval=val%mod;
    multiply_help(1,1,n);
}
ll query_help(int p,int lt,int rt)
{
    // printf("p=%d lt=%d rt=%d sum=%lld add=%lld mul=%lld\n",p,lt,rt,nodes[p].sum,nodes[p].add,nodes[p].mul);
    if(ql<=lt && rt<=qr)return nodes[p].sum;
    ll ans=0;
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    push_down(p,lt,rt);
    if(ql<=mid)ans=(ans+query_help(lc,lt,mid))%mod;
    if(mid<qr)ans=(ans+query_help(rc,mid+1,rt))%mod;
    return ans;
}
ll query(int lt,int rt)
{
    ql=lt, qr=rt;
    return query_help(1,1,n)%mod;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    cin>>n>>m>>mod;
    build(1,1,n);
    while(m--)
    {
        int op,x,y;
        ll k;
        scanf("%d %d %d",&op,&x,&y);
        switch(op)
        {
            case 1:
            scanf("%lld",&k);
            multiply(x,y,k);
            break;
            case 2:
            scanf("%lld",&k);
            add(x,y,k);
            break;
            case 3:
            printf("%lld\n",query(x,y));
            break;
        }
    }
}