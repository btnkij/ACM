/**
 * Number:hdu2586
 * Title:How far away ？
 * Status:AC
 * Tag:[树链剖分]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

const int MAXN=4e4+4;
struct Edge
{
    int from,to,dist;
    int next;
};
Edge edges[MAXN<<1]; int elen;
int head[MAXN];
void AddEdge(int from,int to,int dist)
{
    Edge& e=edges[elen];
    e.from=from, e.to=to, e.dist=dist;
    e.next=head[e.from];
    head[e.from]=elen;
    elen++;
}

int sum[MAXN],slen;

int fa[MAXN],son[MAXN],top[MAXN];
int rk[MAXN],dep[MAXN];
int p[MAXN],rp[MAXN];
void Dfs1(int node,int pre)
{
    rk[node]=1;
    fa[node]=pre;
    dep[node]=dep[pre]+1;
    son[node]=-1;
    int maxs=-1;
    for(int i=head[node]; ~i; i=edges[i].next)
    {
        Edge& e=edges[i];
        if(e.to==pre)continue;
        Dfs1(e.to,node);
        rk[node]+=rk[e.to];
        if(rk[e.to] > maxs)
        {
            son[node]=e.to;
            maxs=rk[e.to];
        }
    }
}
void Dfs2(int node,int mpre)
{
    if(node==-1)return;
    top[node]=mpre;
    p[node]=slen;
    rp[slen]=node;
    slen++;
    Dfs2(son[node],mpre);
    for(int i=head[node]; ~i; i=edges[i].next)
    {
        Edge& e=edges[i];
        if(e.to==fa[node])
        {
            sum[p[node]]=e.dist;
            continue;
        }
        else if(e.to==son[node])continue;
        Dfs2(e.to,e.to);
    }
}
int Query(int u,int v)
{
    int tu=top[u], tv=top[v];
    if(dep[tu]<dep[tv])
    {
        swap(u,v);
        swap(tu,tv);
    }
    int ans=0;
    while(tu!=tv)
    {
        ans+=sum[p[u]]-sum[p[tu]-1];
        u=fa[tu];
        tu=top[u];
    }
    if(u==v)return ans;
    if(dep[u]<dep[v])swap(u,v);
    ans+=sum[p[u]]-sum[p[v]];
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        elen=0;
        slen=1;
        memset(head,-1,sizeof(head));
        int n,m,q;
        scanf("%d %d",&n,&q);
        m=n-1;
        for(int i=0;i<m;i++)
        {
            int u,v,dist;
            scanf("%d %d %d",&u,&v,&dist);
            AddEdge(u,v,dist);
            AddEdge(v,u,dist);
        }
        Dfs1(1,0);
        Dfs2(1,1);
        for(int i=1;i<slen;i++)sum[i]+=sum[i-1];
        while(q--)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            printf("%d\n",Query(u,v));
        }
    }
    return 0;
}