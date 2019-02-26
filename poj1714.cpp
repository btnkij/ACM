/**
 * Number:poj1714
 * Title:Tree
 * Status:AC
 * Tag:[树的点分治]
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

const int MAXN=1e4+4;

struct Edge
{
    int from,to,dist;
};
vector<int> adj[MAXN];
Edge edges[MAXN<<1]; int elen;
int n,m,k;
void AddEdge(int u,int v,int dist)
{
    adj[u].push_back(elen);
    edges[elen].from=u; edges[elen].to=v; edges[elen].dist=dist;
    elen++;
}

bool vis[MAXN];
int rk[MAXN],maxr;
int root,sum;
void DfsSize(int node,int fa)
{
    if(vis[node])return;
    sum++;
    for(int i=0;i<adj[node].size();i++)
    {
        Edge& e=edges[adj[node][i]];
        if(vis[e.to] || e.to==fa)continue;
        DfsSize(e.to,node);
    }
}
void DfsRoot(int node,int fa)
{
    if(vis[node])return;
    rk[node]=0;
    int tmp=0;
    for(int i=0;i<adj[node].size();i++)
    {
        Edge& e=edges[adj[node][i]];
        if(e.to==fa || vis[e.to])continue;
        DfsRoot(e.to,node);
        rk[node]+=rk[e.to]+1;
        tmp=max(tmp,rk[e.to]+1);
    }
    tmp=max(tmp,sum-rk[node]-1);
    if(tmp<maxr)
    {
        maxr=tmp;
        root=node;
    }
}

int dist[MAXN],dlen;
void DfsDist(int node,int fa,int d)
{
    if(vis[node] || d>k)return;
    dist[dlen++]=d;
    for(int i=0;i<adj[node].size();i++)
    {
        Edge& e=edges[adj[node][i]];
        if(e.to==fa || vis[e.to])continue;
        DfsDist(e.to,node,d+e.dist);
    }
}

int Calc(int L,int R)
{
    sort(dist+L,dist+R);
    int lt=L,rt=R-1;
    int cnt=0;
    while(lt<rt)
    {
        if(dist[lt]+dist[rt]<=k)
        {
            cnt+=rt-lt;
            lt++;
        }
        else rt--;
    }
    return cnt;
}

int ans;
void Solve(int node)
{
    maxr=INF;
    sum=0;
    DfsSize(node,0);
    DfsRoot(node,0);
    node=root;
    // printf("enter %d\n",node);
    vis[node]=true;
    dlen=0;
    for(int i=0;i<adj[node].size();i++)
    {
        Edge& e=edges[adj[node][i]];
        if(vis[e.to])continue;
        int L=dlen;
        DfsDist(e.to,0,e.dist);
        int R=dlen;
        ans-=Calc(L,R);
        // printf("ans %d\n",ans);
    }
    ans+=Calc(0,dlen)+dlen;
    // printf("ans %d\n",ans);
    for(int i=0;i<adj[node].size();i++)
    {
        Edge& e=edges[adj[node][i]];
        if(vis[e.to])continue;
        Solve(e.to);
    }
    // printf("exit %d\n",node);
}

int main()
{
    while(scanf("%d %d",&n,&k)!=EOF && n && k)
    {
        memset(vis,false,sizeof(vis));
        ans=0;
        elen=0;
        for(int i=1;i<=n;i++)adj[i].clear();
        m=n-1;
        for(int i=0;i<m;i++)
        {
            int u,v,dist;
            scanf("%d %d %d",&u,&v,&dist);
            AddEdge(u,v,dist);
            AddEdge(v,u,dist);
        }
        Solve(1);
        printf("%d\n",ans);
    }
    return 0;
}