/**
* Number:p5306
* Title:[COCI2019] Transport
* Status:AC
* Tag:[点分治]
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

const int MAXN=1e5+10;
struct Edge
{
    int from,to;
    ll dis;
    int nxt;
}edges[MAXN*2];
int head[MAXN],edge_id;
void addedge(int from,int to,ll dis)
{
    edges[edge_id]=(Edge){from,to,dis,head[from]};
    head[from]=edge_id++;
}

bool cg[MAXN];
int root,rk[MAXN],maxrk,tot;
void getcg(int u,int pre)
{
    rk[u]=1;
    int tmp=-INF;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v] || v==pre)continue;
        getcg(v,u);
        tmp=max(tmp,rk[v]);
        rk[u]+=rk[v];
    }
    tmp=max(tmp,tot-rk[u]);
    if(tmp<maxrk)maxrk=tmp, root=u;
}

ll a[MAXN];
ll ans;
ll fro[MAXN],bac[MAXN];
int len1,len2;
void dfs1(int u,int pre,ll sum,ll mmin)
{
    fro[len1++]=mmin;
    sum+=a[u];
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v] || v==pre)continue;
        ll w=edges[i].dis;
        dfs1(v,u,sum-w,min(mmin,sum-w));
    }
}
void dfs2(int u,int pre,ll sum,ll mmin)
{
    if(mmin>=0)bac[len2++]=sum;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v] || v==pre)continue;
        ll w=edges[i].dis;
        dfs2(v,u,a[v]-w+sum,min(a[v]-w,a[v]-w+mmin));
    }
}
void solve(int src,int n)
{
    maxrk=INF, tot=n;
    getcg(src,-1);
    int u=root;
    cg[u]=true;
    int st1=0, st2=0;
    len1=len2=0;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        ll w=edges[i].dis;
        if(cg[v])continue;
        dfs1(v,u,a[u]-w,a[u]-w);
        dfs2(v,u,a[v]-w,a[v]-w);
        sort(fro+st1,fro+len1);
        sort(bac+st2,bac+len2);
        int l=st1,r=len2-1;
        while(l<len1 && r>=st2)
        {
            while(l<len1 && fro[l]+bac[r]<0)l++;
            ans-=len1-l;
            r--;
        }
        st1=len1,st2=len2;
    }
    sort(fro,fro+len1);
    sort(bac,bac+len2);
    ans+=len2;
    ans+=len1-(lower_bound(fro,fro+len1,0)-fro);
    int l=0,r=len2-1;
    while(l<len1 && r>=0)
    {
        while(l<len1 && fro[l]+bac[r]<0)l++;
        ans+=len1-l;
        r--;
    }
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v])continue;
        solve(v,rk[v]>=rk[u] ? n-rk[u] : rk[v]);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    int n; readi(n);
    rep(i,1,n)scanf("%lld",a+i);
    repne(i,1,n)
    {
        int u,v,w; readi(u,v,w);
        addedge(u,v,w); addedge(v,u,w);
    }
    solve(1,n);
    printf("%lld\n",ans);
    return 0;
}