/**
* Number:p3714
* Title:[BJOI2017]树的难题
* Status:?
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

const int MAXN=2e5+10;
struct Edge
{
    int from,to,color,nxt;
}edges[MAXN*2];
int head[MAXN],edge_id;
void addedge(int from,int to,int color)
{
    edges[edge_id]=(Edge){from,to,color,head[from]};
    head[from]=edge_id++;
}

int root,rk[MAXN],maxrk,tot;
bool cg[MAXN];
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

int n,m,l,r;
int w[MAXN];
int ans;
vector<pair<int,int> > wait;
int same[MAXN],diff[MAXN],cur[MAXN];
void dfs(int u,int pre,int sum,int color,int dep)
{
    if(dep>r)return;
    cur[dep]=max(cur[dep],sum);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(cg[e.to] || e.to==pre)continue;
        if(e.color==color)dfs(e.to,u,sum,color,dep+1);
        else dfs(e.to,u,sum+w[e.color],e.color,dep+1);
    }
}
struct Node
{
    int val,len;
}Q1[MAXN],Q2[MAXN];
int head1,head2,tail1,tail2;
void calc(int color)
{
    head1=head2=tail1=tail2=0;
    Q1[tail1++]=(Node){w[color],0};
    Q2[tail2++]=(Node){0,0};
    for(int i=r;i>=0;i--)
    {
        int nxt=r-i+1;
        while(head1<tail1 && Q1[head1].len+i<l)head1++;
        ans=max(ans,cur[i]+Q1[head1].val-w[color]);
        while(head1<tail1 && same[nxt]>=Q1[tail1-1].val)tail1--;
        Q1[tail1++]=(Node){same[nxt],nxt};
        while(head2<tail2 && Q2[head2].len+i<l)head2++;
        ans=max(ans,cur[i]+Q2[head2].val);
        while(head2<tail2 && diff[nxt]>=Q2[tail2-2].val)tail2--;
        Q2[tail2++]=(Node){diff[nxt],nxt};
    }
}
void solve(int src,int n)
{
    maxrk=INF, tot=n;
    getcg(src,-1);
    int u=root; cg[u]=true;
    wait.clear();
    clr(diff,0xc0);
    diff[0]=0;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(cg[e.to])continue;
        wait.emplace_back(e.color,e.to);
    }
    sort(wait.begin(),wait.end());
    int sz=wait.size();
    for(int i=0,j=0;i<sz;i=j)
    {
        clr(same,0xc0);
        while(j<sz && (j==i || wait[j-1].first==wait[j].first))
        {
            clr(cur,0xc0);
            dfs(wait[j].second,u,w[wait[j].first],wait[j].first,1);
            calc(wait[i].first);
            rep(i,0,r)same[i]=max(same[i],cur[i]);
            j++;
        }
        rep(i,0,r)diff[i]=max(diff[i],same[i]);
    }
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v])continue;
        solve(v,rk[v]<rk[u]?rk[v]:n-rk[u]);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ans=-INF;
    clr(head,-1);
    readi(n,m,l,r);
    rep(i,1,m)readi(w[i]);
    repne(i,1,n)
    {
        int u,v,c; readi(u,v,c);
        addedge(u,v,c); addedge(v,u,c);
    }
    solve(1,n);
    printf("%d",ans);
    return 0;
}