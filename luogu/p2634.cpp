/**
* Number:p2634
* Title:[国家集训队]聪聪可可
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

const int MAXN=2e4+10;
struct Edge
{
    int from,to,w,nxt;
}edges[MAXN*2];
int head[MAXN],edge_id;
void addedge(int from,int to,int w)
{
    edges[edge_id]=(Edge){from,to,w,head[from]};
    head[from]=edge_id++;
}

int root,tot,rk[MAXN],maxrk;
bool cg[MAXN];
void getcg(int u,int pre)
{
    rk[u]=1;
    int tmp=-INF;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre || cg[v])continue;
        getcg(v,u);
        tmp=max(tmp,rk[v]);
        rk[u]+=rk[v];
    }
    tmp=max(tmp,tot-rk[u]);
    if(tmp<maxrk)root=u,maxrk=tmp;
}
int a,b;
int allcnt[4],cnt[4];
void dfs(int u,int sum,int pre)
{
    sum=(sum%3+3)%3;
    cnt[sum]++;
    if(sum==0)a+=allcnt[0]+1;
    else a+=allcnt[3-sum];
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre || cg[v])continue;
        int w=edges[i].w;
        int t=sum+w;
        dfs(v,t,u);
    }
}
void solve(int u,int nn)
{
    maxrk=INF,tot=nn;
    getcg(u,-1); cg[root]=true;
    clr(allcnt,0);
    for(int i=head[root];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v])continue;
        clr(cnt,0);
        dfs(v,edges[i].w,-1);
        for(int i=0;i<3;i++)allcnt[i]+=cnt[i];
    }
    for(int i=head[root];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v])continue;
        solve(v,rk[v]>rk[root]?nn-rk[root]:rk[v]);
    }
}

int gcd(int a,int b)
{
    return b==0 ? a : gcd(b,a%b);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    int n; readi(n);
    repne(i,1,n)
    {
        int x,y,w; readi(x,y,w);
        addedge(x,y,w); addedge(y,x,w);
    }
    solve(1,n);
    b=n*n;
    a=a*2+n;
    int d=gcd(a,b);
    printf("%d/%d",a/d,b/d);
    return 0;
}