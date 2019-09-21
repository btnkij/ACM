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
    int from,to,nxt;
}edges[MAXN*2];
int head[MAXN],edge_id;
void addedge(int from,int to)
{
    edges[edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id++;
}

ll sum[MAXN];
void add(int idx,int val)
{
    while(idx<MAXN)
    {
        sum[idx]+=val;
        idx+=idx&-idx;
    }
}
ll query(int idx)
{
    ll ans=0;
    while(idx)
    {
        ans+=sum[idx];
        idx^=idx&-idx;
    }
    return ans;
}

struct Node
{
    int id,dfn,sz,rk,t;
    bool operator<(const Node& rhs)const
    {
        return rk<rhs.rk;
    }
}nodes[MAXN];

int timer;
void dfs(int u,int pre)
{
    Node& nod=nodes[u];
    nod.dfn=++timer;
    nod.sz=1;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs(v,u);
        nod.sz+=nodes[v].sz;
    }
}

ll ans[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    int n; readi(n);
    int root;
    rep(i,1,n)
    {
        int m,r,t; readi(m,r,t);
        if(m==-1)root=i;
        else addedge(m,i);
        nodes[i]=(Node){i,0,0,r,t};
    }
    dfs(root,-1);
    sort(nodes+1,nodes+n+1);
    for(int i=1,j;i<=n;i=j)
    {
        for(j=i; j<=n && (j==i || nodes[j].rk==nodes[j-1].rk); j++)
        {
            Node& nod=nodes[j];
            ll s=query(nod.dfn+nod.sz-1)-query(nod.dfn);
            ans[nod.id]=s;
        }
        for(int k=i;k<j;k++)
        {
            Node& nod=nodes[k];
            add(nod.dfn, nod.t);
        }
    }
    rep(i,1,n)printf("%lld\n",ans[i]);
    return 0;
}