/**
* Number:sp2939
* Title:QTREE5 - Query on a tree V
* Status:AC
* Tag:[动态点分治]
**/

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

const int MAXN=1e5+10;
struct Edge
{
    int from,to,nxt;
}edges[MAXN*2];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]={from,to,head[from]};
    head[from]=edgeid++;
}

struct Heap
{
    priority_queue<int,vector<int>,greater<int>> open,close;
    int size()
    {
        return open.size()-close.size();
    }
    void push(int val)
    {
        open.push(val);
    }
    void pop(int val)
    {
        close.push(val);
    }
    int top()
    {
        while(!close.empty() && open.top()==close.top())
            open.pop(),close.pop();
        return open.top();
    }
};

struct Node
{
    int color;
    int fa,dep,up[20];
    Heap dis;
}tree[MAXN];
int root,totrk,rk[MAXN],maxrk;
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
    tmp=max(tmp,totrk-rk[u]);
    if(tmp<maxrk)maxrk=tmp, root=u;
}
void dfs(int u,int pre,int dep)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre || cg[v])continue;
        tree[v].up[dep]=tree[u].up[dep]+1;
        dfs(v,u,dep);
    }
}
void build(int u,int pre,int dep,int totrk)
{
    ::totrk=totrk, maxrk=INF;
    getcg(u,0);
    cg[u=root]=true;
    Node& cur=tree[u];
    cur.fa=pre, cur.dep=dep, cur.color=0;
    dfs(u,0,dep);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(cg[v])continue;
        if(rk[v]>rk[u])rk[v]=totrk-rk[u];
        build(v,u,dep+1,rk[v]);
    }
}
void change(int u)
{
    Node& nod=tree[u];
    nod.color^=1;
    if(nod.color==1)
        for(int x=u;x;x=tree[x].fa)
            tree[x].dis.push(nod.up[tree[x].dep]);
    else
        for(int x=u;x;x=tree[x].fa)
            tree[x].dis.pop(nod.up[tree[x].dep]);
}
int query(int u)
{
    int ans=INF;
    for(int x=u;x;x=tree[x].fa)
        if(tree[x].dis.size())
            ans=min(ans,tree[u].up[tree[x].dep]+tree[x].dis.top());
    return ans==INF?-1:ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    clr(head,-1), edgeid=0;
    repne(i,1,n)
    {
        int u,v; readi(u,v);
        addedge(u,v), addedge(v,u);
    }
    build(1,0,1,n);
    int q; readi(q);
    while(q--)
    {
        int op,x; readi(op,x);
        if(op==0)change(x);
        else if(op==1)printf("%d\n",query(x));
    }
    return 0;
}