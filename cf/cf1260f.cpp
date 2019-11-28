// unfinished

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

const ll MOD=1e9+7;
const int MAXN=2e2+10;

struct Edge
{
    int from,to,nxt;
}edges[MAXN*2];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

ll inv[MAXN];
void init_inv()
{
    inv[1] = 1;
    for(int i = 2; i < MAXN; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}

ll sum[MAXN*4],addv[MAXN*4],setv[MAXN*4];
void pushup(int p)
{
    sum[p]=sum[p<<1]+sum[p<<1|1];
}
void pushdown(int p,int lt,int rt)
{
    int lc=p<<1,rc=p<<1|1;
    if(setv[p])
    {
        sum[p<<1]=sum[p<<1|1]=addv[p<<1]=addv[p<<1|1]=setv[p]=0;
        setv[lc]=setv[rc]=1;
    }
    if(addv[p])
    {
        int mid=(lt+rt)>>1;
        sum[lc]=(sum[lc]+addv[p]*(mid-lt+1)%MOD)%MOD;
        sum[rc]=(sum[rc]+addv[p]*(rt-mid)%MOD)%MOD;
        addv[lc]=(addv[lc]+addv[p])%MOD;
        addv[rc]=(addv[rc]+addv[p])%MOD;
        addv[p]=0;
    }
}
void update(int p,int lt,int rt,int qlt,int qrt,int qval)
{
    if(qlt<=lt && rt<=qrt)
    {
        sum[p]=(sum[p]+qval*(rt-lt+1)%MOD)%MOD;
        addv[p]=(addv[p]+qval)%MOD;
        return;
    }
    pushdown(p,lt,rt);
    int mid=(lt+rt)>>1;
    if(qlt<=mid)update(p<<1,lt,mid,qlt,qrt,qval);
    if(mid<qrt)update(p<<1|1,mid+1,rt,qlt,qrt,qval);
}
ll query(int p,int lt,int rt,int qlt,int qrt)
{
    if(qlt<=lt && rt<=qrt)return sum[p];
    pushdown(p,lt,rt);
    ll ans=0;
    int mid=(lt+rt)>>1;
    if(qlt<=mid)ans+=query(p<<1,lt,mid,qlt,qrt);
    if(mid<qrt)ans+=query(p<<1|1,mid+1,rt,qlt,qrt);
    return ans;
}

ll all;
int n,l[MAXN],r[MAXN],ncolor;
int root,maxsz,sz[MAXN],tot;
bool cg[MAXN];
ll ans;
vector<pair<int,int> > ans1;
void getcg(int u,int pre)
{
    sz[u]=1;
    int tmp=0;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre || cg[v])continue;
        getcg(v,u);
        sz[u]+=sz[v];
        tmp=max(tmp,sz[v]);
    }
    tmp=max(tmp,n-sz[u]);
    if(tmp<maxsz)maxsz=tmp,root=u;
}
void dfs(int u,int dep,int pre)
{
    ll t=query(1,1,ncolor,l[u],r[u])*dep%MOD*inv[r[u]-l[u]+1]%MOD;
    ans=(ans+t)%MOD;
    if(!(l[u]>r[root] || r[u]<l[root]))
    {
        int L=min(r[root],r[u])-max(l[root],l[u])+1;
        t=all*inv[r[root]-l[root]+1]%MOD*inv[r[u]-l[u]+1]%MOD*(dep*L)%MOD;
        ans=(ans+t)%MOD;
    }
    ans1.emplace_back(u,dep);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v] || v==pre)continue;
        dfs(v,dep+1,u);
    }
}
void solve(int u,int n)
{
    tot=n;
    maxsz=INF; getcg(u,-1); cg[root]=true;
    sum[1]=0,setv[1]=1;
    for(int i=head[root];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v])continue;
        ans1.clear();
        dfs(v,1,-1);
        for(auto it:ans1)
        {
            int k=it.first,d=it.second;
            update(1,1,ncolor,l[k],r[k],d*all%MOD*inv[r[k]-l[k]+1]%MOD);
        }
    }
    for(int i=head[root];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v])continue;
        solve(v,sz[v]>sz[root]?n-sz[root]:sz[v]);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    init_inv();
    clr(head,-1);
    readi(n);
    all=1;
    rep(i,1,n)
    {
        readi(l[i],r[i]);
        all=all*(r[i]-l[i]+1)%MOD;
        ncolor=max(ncolor,r[i]);
    }
    repne(i,1,n)
    {
        int u,v; readi(u,v);
        addedge(u,v); addedge(v,u);
    }
    ans=0;
    solve(1,n);
    printf("%lld\n",ans);
    return 0;
}