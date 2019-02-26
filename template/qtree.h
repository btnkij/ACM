/**
 * 
 * 树链剖分
 * 
**/

#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN=1e5+10;

struct Node;
struct Edge
{
    int to, nxt;
}edges[MAXN<<1];
struct Node
{
    ll val;
    int first_edge;
    int dep, rank, pos;
    int fa, son, top;
}nodes[MAXN];

int n_edge;
void add_edge(int from,int to)
{
    Edge& e=edges[n_edge];
    e.to=to;
    e.nxt=nodes[from].first_edge;
    nodes[from].first_edge=n_edge++;
}

void dfs1(int id,int pre)
{
    Node& cur=nodes[id];
    cur.fa=pre;
    cur.dep=nodes[pre].dep+1;
    int maxrk=cur.rank=1;
    for(int i=cur.first_edge; ~i; i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs1(v,id);
        cur.rank+=nodes[v].rank;
        if(nodes[v].rank >= maxrk)
        {
            maxrk=nodes[v].rank;
            cur.son=v;
        }
    }
}

int timer=1;
int rpos[MAXN];
void dfs2(int id,int top)
{
    Node& cur=nodes[id];
    cur.pos=timer;
    rpos[timer++]=id;
    cur.top=top;
    if(cur.son)dfs2(cur.son, top);
    for(int i=cur.first_edge; ~i; i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==cur.fa || v==cur.son)continue;
        dfs2(v, v);
    }
}

int n;
ll mod;
struct SegTreeNode
{
    ll sum, lazy;
}segtree[MAXN<<2];

void push_up(int p)
{
    segtree[p].sum=segtree[p<<1].sum+segtree[p<<1|1].sum;
}

void push_down(int p, int lt, int rt)
{
    if(!segtree[p].lazy)return;
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    segtree[lc].sum=segtree[lc].sum+segtree[p].lazy*(mid-lt+1);
    segtree[lc].lazy=segtree[lc].lazy+segtree[p].lazy;
    segtree[rc].sum=segtree[rc].sum+segtree[p].lazy*(rt-mid);
    segtree[rc].lazy=segtree[rc].lazy+segtree[p].lazy;
    segtree[p].lazy=0;
}

void build(int p, int lt, int rt)
{
    if(lt==rt)
    {
        segtree[p].sum=nodes[rpos[lt]].val;
        return;
    }
    int mid=(lt+rt)>>1;
    build(p<<1, lt, mid);
    build(p<<1|1, mid+1, rt);
    push_up(p);
}

int qlt, qrt;
ll qval;
void add_help(int p, int lt, int rt)
{
    if(qlt<=lt && rt<=qrt)
    {
        segtree[p].sum=segtree[p].sum+qval*(rt-lt+1);
        segtree[p].lazy=segtree[p].lazy+qval;
        return;
    }
    push_down(p, lt, rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(qlt<=mid)add_help(lc, lt, mid);
    if(mid<qrt)add_help(rc, mid+1, rt);
    push_up(p);
}
void add(int lt, int rt, ll val)
{
    qlt=lt, qrt=rt, qval=val%mod;
    add_help(1,1,n);
}

ll query_help(int p, int lt, int rt)
{
    if(qlt<=lt && rt<=qrt)return segtree[p].sum;
    push_down(p, lt, rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    ll ans=0;
    if(qlt<=mid)ans=query_help(lc, lt, mid);
    if(mid<qrt)ans=ans+query_help(rc, mid+1, rt);
    return ans;
}
ll query(int lt, int rt)
{
    qlt=lt, qrt=rt;
    return query_help(1,1,n);
}

void add_chain(int x, int y, ll val)
{
    int topx=nodes[x].top, topy=nodes[y].top;
    while(topx != topy)
    {
        if(nodes[topx].dep>=nodes[topy].dep)
        {
            add(nodes[topx].pos, nodes[x].pos, val);
            x=nodes[topx].fa;
            topx=nodes[x].top;
        }
        else
        {
            add(nodes[topy].pos, nodes[y].pos, val);
            y=nodes[topy].fa;
            topy=nodes[y].top;
        }
    }
    if(nodes[x].dep>nodes[y].dep)swap(x,y);
    add(nodes[x].pos, nodes[y].pos, val);
}

ll query_chain(int x, int y)
{
    ll ans=0;
    int topx=nodes[x].top, topy=nodes[y].top;
    while(topx != topy)
    {
        if(nodes[topx].dep>=nodes[topy].dep)
        {
            ans=ans+query(nodes[topx].pos, nodes[x].pos);
            x=nodes[topx].fa;
            topx=nodes[x].top;
        }
        else
        {
            ans=ans+query(nodes[topy].pos, nodes[y].pos);
            y=nodes[topy].fa;
            topy=nodes[y].top;
        }
    }
    if(nodes[x].dep>nodes[y].dep)swap(x,y);
    ans=ans+query(nodes[x].pos,nodes[y].pos);
    return ans;
}