/**
* Number:p4116
* Title:Qtree3
* Status:AC
* Tag:[树链剖分, 线段树]
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
}edges[MAXN<<1];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]={from,to,head[from]};
    head[from]=edgeid++;
}

struct QTreeNode
{
    int dep,sz,pos,fa,son,top;
}nodes[MAXN];
int dfsid=0, rpos[MAXN];
void dfs1(int u,int pre)
{
    QTreeNode& cur=nodes[u];
    cur.fa=pre, cur.dep=nodes[pre].dep+1, cur.sz=1;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs1(v,u);
        cur.sz+=nodes[v].sz;
        if(nodes[v].sz>nodes[cur.son].sz)
            cur.son=v;
    }
}
void dfs2(int u,int top)
{
    QTreeNode& cur=nodes[u];
    cur.pos=++dfsid, rpos[dfsid]=u;
    cur.top=top;
    if(cur.son)dfs2(cur.son,top);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==cur.fa || v==cur.son)continue;
        dfs2(v,v);
    }
}

int first[MAXN<<2];
void build()
{
    clr(first,-1);
}
void pushup(int p)
{
    if(first[p<<1]!=-1)first[p]=first[p<<1];
    else first[p]=first[p<<1|1];
}
void update(int p,int lt,int rt,int qpos)
{
    if(lt==rt)
    {
        first[p]=(first[p]==-1?rpos[lt]:-1);
        return;
    }
    int mid=(lt+rt)>>1;
    if(qpos<=mid)update(p<<1,lt,mid,qpos);
    else update(p<<1|1,mid+1,rt,qpos);
    pushup(p);
}
int query(int p,int lt,int rt,int qlt,int qrt)
{
    if(qlt<=lt && rt<=qrt)return first[p];
    int mid=(lt+rt)>>1, ans=-1;
    if(qlt<=mid)ans=query(p<<1,lt,mid,qlt,qrt);
    if(ans==-1 && mid<qrt)ans=query(p<<1|1,mid+1,rt,qlt,qrt);
    return ans;
}

int query_chain(int n,int x,int y)
{
    int ans=-1;
    int topx=nodes[x].top, topy=nodes[y].top;
    while(topx!=topy)
    {
        if(nodes[topx].dep>nodes[topy].dep)
            swap(topx,topy), swap(x,y);
        int tmp=query(1,1,n,nodes[topy].pos,nodes[y].pos);
        if(tmp!=-1)ans=tmp;
        y=nodes[topy].fa, topy=nodes[y].top;
    }
    if(nodes[x].dep>nodes[y].dep)swap(x,y);
    int tmp=query(1,1,n,nodes[x].pos,nodes[y].pos);
    if(tmp!=-1)ans=tmp;
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,q; readi(n,q);
    clr(head,-1), edgeid=0;
    repne(i,1,n)
    {
        int u,v; readi(u,v);
        addedge(u,v), addedge(v,u);
    }
    dfs1(1,0), dfs2(1,1);
    build();
    while(q--)
    {
        int op,x; readi(op,x);
        if(op==0)update(1,1,n,nodes[x].pos);
        else if(op==1)printf("%d\n",query_chain(n,1,x));
    }
    return 0;
}