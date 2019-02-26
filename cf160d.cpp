/**
 * Number:cf160d
 * Title:Edges in MST
 * Status:WA
 * Tag:[]
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

const int MAXN=1e5+4;

struct Edge
{
    int from,to;
    int dist;
    Edge(int from,int to,int dist)
    {
        this->from=from; this->to=to; this->dist=dist;
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

bool vis[MAXN];
int diste[MAXN],cnte[MAXN];
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
    memset(vis,false,sizeof(vis));
    memset(diste,-1,sizeof(diste));
    memset(cnte,0,sizeof(cnte));
    priority_queue<HeapNode> Q;
    cnte[1]=1;
    vis[1]=true;
    for(int it:adj[1])
        Q.push((HeapNode){it,edges[it].dist});
    while(!Q.empty())
    {
        HeapNode node=Q.top();
        const Edge& e=edges[node.id];
        Q.pop();
        if(vis[e.to] && e.dist!=diste[e.to])continue;
        vis[e.to]=true;
        diste[e.to]=e.dist;
        cnte[e.to]++;
        // printf("from=%d to=%d dist=%d\n",e.from,e.to,e.dist);
        // printf("diste[%d]=%d\n",e.to,diste[e.to]);
        // printf("cnte[%d]=%d\n",e.to,cnte[e.to]);
        for(int it:adj[e.to])
        {
            if(vis[edges[it].to])continue;
            Q.push((HeapNode){it,edges[it].dist});
        }
    }
}

int main()
{
    int m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v,dist;
        scanf("%d %d %d",&u,&v,&dist);
        AddEdge(u,v,dist);
    }
    Prim();
    m<<=1;
    for(int i=0;i<m;i+=2)
    {
        const Edge& e=edges[i];
        if(diste[e.from]==e.dist || diste[e.to]==e.dist)
        {
            if(cnte[e.from]==1 && cnte[e.to]==1)
                printf("any\n");
            else
                printf("at least one\n");
        }
        else
            printf("none\n");
        
    }
    return 0;
}