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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=1e6+10;
struct Edge
{
    int from,to;
}edges[MAXN*2];
int head[MAXN],nxt[MAXN*2],ne;
void add_edge(int from,int to)
{
    Edge& e=edges[ne];
    e.from=from, e.to=to;
    nxt[ne]=head[from];
    head[from]=ne++;
}

int fa[MAXN], rk[MAXN], son[MAXN];
void dfs1(int u,int pre)
{
    fa[u]=pre;
    rk[u]=1;
    int tmp=-INF;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs1(v,u);
        rk[u]+=rk[v];
        if(rk[v]>tmp)
        {
            tmp=rk[v];
            son[u]=v;
        }
    }
}
int pos[MAXN], rpos[MAXN], top[MAXN], timer;
void dfs2(int u,int pre)
{
    top[u]=pre;
    pos[u]=timer++;
    rpos[pos[u]]=u;
    if(!son[u])return;
    dfs2(son[u],pre);
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==son[u] || v==fa[u])continue;
        dfs2(v,v);
    }
}

int n,q,root;
ll sum[MAXN<<2];
int w[MAXN];
void pushup(int p)
{
    sum[p]=sum[p<<1]+sum[p<<1|1];
}
void build(int p,int lt,int rt)
{
    if(lt==rt)
    {
        sum[p]=w[rpos[lt]];
        return;
    }
    int mid=(lt+rt)>>1;
    int lc=p<<1, rc=lc|1;
    if(mid>=lt)build(lc,lt,mid);
    if(mid<rt)build(rc,mid+1,rt);
    pushup(p);
}
int qlt,qrt;
ll qval;
void addhelp(int p,int lt,int rt)
{
    if(lt==rt && lt==qlt)
    {
        sum[p]+=qval;
        return;
    }
    int mid=(lt+rt)>>1;
    int lc=p<<1, rc=lc|1;
    if(mid>=qlt)addhelp(lc,lt,mid);
    else addhelp(rc,mid+1,rt);
    pushup(p);
}
void add(int p,int val)
{
    qlt=pos[p], qval=val;
    addhelp(1,1,n);
}
ll queryhelp(int p,int lt,int rt)
{
    if(qlt<=lt && rt<=qrt)return sum[p];
    int mid=(lt+rt)>>1;
    int lc=p<<1, rc=lc|1;
    ll ans=0;
    if(mid>=qlt)ans+=queryhelp(lc,lt,mid);
    if(mid<qrt)ans+=queryhelp(rc,mid+1,rt);
    return ans;
}
ll querychain(int lt,int rt)
{
    qlt=lt,qrt=rt;
    return queryhelp(1,1,n);
}

ll querytree(int p)
{
    return querychain(pos[p],pos[p]+rk[p]-1);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,q,root);
    ne=0;
    rep(i,1,n)
    {
        readi(w[i]);
        head[i]=-1;
    }
    repne(i,1,n)
    {
        int u,v; readi(u,v);
        add_edge(u,v); add_edge(v,u);
    }
    dfs1(root,0);
    timer=1;
    dfs2(root,root);
    build(1,1,n);
    while(q--)
    {
        int op; readi(op);
        if(op==1)
        {
            int y,b; readi(y,b);
            add(y,b);
        }
        else if(op==2)
        {
            int y; readi(y);
            printf("%lld\n",querytree(y));
        }
    }
    return 0;
}