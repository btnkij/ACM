/**
 * Number:uva1354
 * Title:Bond
 * Status:AC
 * Tag:[mst,并查集]
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

const int MAXN=5e4+4;
const int MAXM=1e5+4;

struct Edge
{
    int from,to,dist;
    bool operator<(const Edge& rhs)const
    {
        return this->dist < rhs.dist;
    }
}edges[MAXM];

int dist[MAXN];
int par[MAXN],rk[MAXN];
int lchain[MAXN];
int findRoot(int x)
{
    return x==par[x] ? x : findRoot(par[x]);
}
bool merge(int x,int y,int d)
{
    int rx=findRoot(x),ry=findRoot(y);
    if(rx==ry)return false;
    if(rk[rx]<rk[ry])
        par[rx]=ry,dist[rx]=d;
    else
    {
        par[ry]=rx,dist[ry]=d;
        if(rk[rx]==rk[ry])rk[rx]++;
    }
    return true;
}
int query(int x, int y) 
{
    int ans1=0,ans2=-1;
    int u=x;
    while(true) 
    {
        lchain[u]=ans1;
        if(u==par[u])break;
        ans1=max(ans1,dist[u]);
        u=par[u];
    }
    u=y;
    while(true) 
    {
        if(lchain[u]>=0) 
        {
            ans2=max(ans2, lchain[u]); 
            break;
        }
        if(u==par[u])break;
        ans2=max(ans2,dist[u]);
        u=par[u];
    }
    u=x;
    while(true) 
    {
        lchain[u]=-1;
        if(u==par[u])break;
        u=par[u];
    }
    return ans2;
}

int main()
{
    bool first=true;
    int n,m;
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;i++)par[i]=i,rk[i]=1,lchain[i]=-1;
        for(int i=0;i<m;i++)
            scanf("%d %d %d",&edges[i].from,&edges[i].to,&edges[i].dist);
        sort(edges,edges+m);
        int cnt=n-1;
        for(int i=0;i<m;i++)
        {
            const Edge& e=edges[i];
            if(merge(e.from,e.to,e.dist))
            {
                cnt--;
                if(cnt==0)break;
            }
        }
        if(!first)printf("\n");
        first=false;
        int q; scanf("%d",&q);
        while(q--)
        {
            int from,to;
            scanf("%d %d",&from,&to);
            printf("%d\n",query(from,to));
        }
    }
    return 0;
}

// int nNode;
// struct _Graph
// {
//     struct Edge
//     {
//         int from,to;
//         int dist;
//         Edge(int from,int to,int dist)
//         {
//             this->from=from; this->to=to; this->dist=dist;
//         }
//         bool operator<(const Edge& rhs)const
//         {
//             return this->dist < rhs.dist;
//         }
//     };
//     int nNode;
//     std::vector<Edge> edges;
//     std::vector<int> adj[MAXN];
//     void Init()
//     {
//         edges.clear();
//         for(int i=1;i<=nNode;i++)adj[i].clear();
//     }
//     void AddArc(int from,int to,int dist)
//     {
//         adj[from].push_back(edges.size());
//         edges.push_back(Edge(from,to,dist));
//     }
//     void AddEdge(int u,int v,int dist)
//     {
//         AddArc(u,v,dist);
//         AddArc(v,u,dist);
//     }
// }G;

// int top[MAXN];
// int fa[MAXN];
// int dep[MAXN];
// int cntSon[MAXN];
// int p[MAXN],rp[MAXN];
// int son[MAXN];
// int pos;
// void init()
// {
//     pos=0;
//     memset(son,-1,sizeof(son));
// }
// void dfs1(int u,int pre,int depth)
// {
//     dep[u]=depth; fa[u]=pre; cntSon[u]=1;
//     for(int i:G.adj[u])
//     {
//         auto& e=G.edges[i];
//         if(e.to!=pre)
//         {
//             dfs1(e.to,u,depth+1);
//             cntSon[u]+=cntSon[e.to];
//             if(son[u]==-1 || cntSon[e.to]>cntSon[son[u]])
//                 son[u]=e.to;
//         }
//     }
// }
// void dfs2(int u,int sp)
// {
//     top[u]=sp; p[u]=pos++; rp[p[u]]=u;
//     if(son[u]==-1)return;
//     dfs2(son[u],sp);
//     for(int i:G.adj[u])
//     {
//         auto& e=G.edges[i];
//         if(e.to!=son[u] && e.to!=fa[u])
//             dfs2(e.to,e.to);
//     }
// }

// struct _SegTree
// {
//     int qleft,qright;
//     int tree[MAXN<<2];
//     void update()
// }segtree;

// struct _LCA
// {
//     int timer;
//     int ancestor[MAXN][LOGN];
//     int tin[MAXN],tout[MAXN];
//     int maxEdge[MAXN][LOGN];
//     void dfs(int u,int fa)
//     {
//         tin[u]=timer++;
//         ancestor[u][0]=fa;
//         for(int i=1;i<LOGN;i++)
//             ancestor[u][i]=ancestor[ancestor[u][i-1]][i-1];
//         for(int i : G.adj[u])
//         {
//             const auto& e=G.edges[i];
//             if(e.to!=fa)
//             {
//                 maxEdge[e.to][0]=e.dist;
//                 for(int i=1;i<LOGN;i++)
//                     maxEdge[e.to][i]=max(maxEdge[u][i-1],e.dist);
//                 dfs(e.to,u);
//             }
//         }
//         tout[u]=timer++;
//     }
//     bool isAncestor(int fa,int u)
//     {
//         return fa==0 || (tin[fa]<=tin[u] && tout[u]<=tout[fa]);
//     }
//     int query(int u,int v)
//     {
//         int fa;
//         if(isAncestor(u,v))fa=u;
//         else if(isAncestor(v,u))fa=v;
//         else
//         {
//             int x=u;
//             for(int i=LOGN;i>=0;i--)
//                 if(!isAncestor(ancestor[u][i],v))
//                     x=ancestor[x][i];
//             fa=ancestor[x][0];
//         }
//         int maxe=0;
//         if(u!=fa)
//         {
//             int x=u;
//             for(int i=LOGN;i>=0;i--)
//                 if(!isAncestor(ancestor[u][i],v))
//                 {
//                     maxe=max(maxe,maxEdge[x][i]);
//                     x=ancestor[x][i];
//                 }
//             maxe=max(maxe,maxEdge[x][0]);
//         }
//         if(v!=fa)
//         {
//             int x=v;
//             for(int i=LOGN;i>=0;i--)
//                 if(!isAncestor(ancestor[v][i],u))
//                 {
//                     maxe=max(maxe,maxEdge[x][i]);
//                     x=ancestor[x][i];
//                 }
//             maxe=max(maxe,maxEdge[x][0]);
//         }
//         return maxe;
//     }
//     void Init()
//     {
//         timer=0;
//         memset(ancestor,0,sizeof(ancestor));
//         dfs(1,0);
//     }
// }lca;

// vector<_Graph::Edge> roads;
// int par[MAXN];
// int findRoot(int x)
// {
//     return x==par[x] ? x : par[x]=findRoot(par[x]);
// }

// int main()
// {
//     bool first=true;
//     int m;
//     while(scanf("%d %d",&nNode,&m)!=EOF)
//     {
//         roads.clear();
//         for(int i=0;i<m;i++)
//         {
//             int u,v,dist;
//             scanf("%d %d %d",&u,&v,&dist);
//             roads.emplace_back(u,v,dist);
//         }
//         for(int i=1;i<=nNode;i++)par[i]=i;
//         sort(roads.begin(),roads.end());
//         int cnt=nNode-1;
//         G.Init();
//         for(const auto& e : roads)
//         {
//             int x=findRoot(e.from),y=findRoot(e.to);
//             if(x!=y)
//             {
//                 par[x]=y;
//                 G.AddEdge(e.from,e.to,e.dist);
//                 cnt--;
//                 if(cnt==0)break;
//             }
//         }
//         lca.Init();
//         int q;
//         scanf("%d",&q);
//         if(!first)printf("\n\n");
//         first=false;
//         while(q--)
//         {
//             int u,v;
//             scanf("%d %d",&u,&v);
//             printf("%d",lca.query(u,v));
//             if(q)putchar('\n');
//         }
//     }
//     return 0;
// }