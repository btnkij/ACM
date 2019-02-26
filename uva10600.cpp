/**
 * Number:uva10600
 * Title:ACM Contest and Blackout
 * Status:AC
 * Tag:[最小生成树,次小生成树]
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

const int MAXN=1010;

struct Edge
{
    int from,to;
    int dist;
    Edge(int from,int to,int dist)
    {
        this->from=from;
        this->to=to;
        this->dist=dist;
    }
    bool operator<(const Edge& rhs)const
    {
        return this->dist > rhs.dist;
    }
};
int n;
vector<Edge> edges;
vector<int> adj[MAXN];
void AddEdge(int from,int to,int dist)
{
    adj[from].push_back(edges.size());
    edges.push_back(Edge(from,to,dist));
    adj[to].push_back(edges.size());
    edges.push_back(Edge(to,from,dist));
}

int maxedge[MAXN][MAXN];
bool vis[MAXN],onMst[MAXN*MAXN];
int mst;
struct HeapNode
{
    int id,dist;
    bool operator<(const HeapNode& rhs)const
    {
        return this->dist > rhs.dist;
    }
};
void Prim()
{
    mst=0;
    memset(vis,false,sizeof(vis));
    memset(onMst,false,sizeof(onMst));
    memset(maxedge,0,sizeof(maxedge));
    priority_queue<HeapNode> Q;
    vis[1]=true;
    for(int it:adj[1])
        Q.push((HeapNode){it,edges[it].dist});
    int cnt=n-1;
    while(!Q.empty() && cnt>0)
    {
        HeapNode node=Q.top();
        Edge& e=edges[node.id];
        Q.pop();
        if(vis[e.to])continue;
        for(int i=1;i<=n;i++)
        {
            if(vis[i])
            {
                maxedge[i][e.to]=maxedge[e.to][i]=max(e.dist,maxedge[e.from][i]);
            }
        }
        mst+=e.dist;
        vis[e.to]=true;
        onMst[node.id]=onMst[node.id^1]=true;
        cnt--;
        for(int it:adj[e.to])
        {
            if(vis[edges[it].to])continue;
            Q.push((HeapNode){it,edges[it].dist});
        }
    }
}

int main()
{
    int T; scanf("%d",&T);
    while(T--)
    {
        int m;
        scanf("%d %d",&n,&m);
        edges.clear();
        for(int i=1;i<=n;i++)adj[i].clear();
        while(m--)
        {
            int u,v,dist;
            scanf("%d %d %d",&u,&v,&dist);
            AddEdge(u,v,dist);
        }
        Prim();
        int mst2=INF;
        for(int i=0;i<edges.size();i++)
        {
            if(!onMst[i])
            {
                Edge& e=edges[i];
                mst2=min(mst2, mst+e.dist-maxedge[e.from][e.to]);
            }
        }
        printf("%d %d\n",mst,mst2);
    }
    return 0;
}