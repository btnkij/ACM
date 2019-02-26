/**
 * Number:uva12661
 * Title:Funny Car Racing
 * Status:AC
 * Tag:[动态边权的dijkstra]
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

int n,m,s,t;
struct Edge
{
    int from,to,open,close,dist;
};
vector<Edge> edges;
vector<int> adj[304];
void AddEdge(int from,int to,int open,int close,int dist)
{
    adj[from].push_back(edges.size());
    edges.push_back((Edge){from,to,open,close,dist});
}
struct HeapNode
{
    int now,pos;
    bool operator<(const HeapNode& rhs)const
    {
        return this->now > rhs.now;
    }
};
bool vis[304];
int bfs()
{
    memset(vis,0,sizeof(vis));
    priority_queue<HeapNode> Q;
    Q.push((HeapNode){0,s});
    while(!Q.empty())
    {
        HeapNode node=Q.top();
        Q.pop();
        if(vis[node.pos])continue;
        if(node.pos==t)return node.now;
        vis[node.pos]=true;
        for(int i:adj[node.pos])
        {
            Edge& e=edges[i];
            if(vis[e.to])continue;
            if(node.now%e.close+e.dist<=e.open)
                Q.push((HeapNode){node.now+e.dist,e.to});
            else
                Q.push((HeapNode){
                    (node.now/e.close+1)*e.close+e.dist,e.to
                    });
        }
    }
    return INF;
}
int main()
{
    int kase=1;
    while(scanf("%d %d %d %d",&n,&m,&s,&t)!=EOF)
    {
        edges.clear();
        for(int i=1;i<=n;i++)adj[i].clear();
        for(int i=0;i<m;i++)
        {
            int u,v,a,b,t;
            scanf("%d %d %d %d %d",&u,&v,&a,&b,&t);
            if(t>a)continue;
            AddEdge(u,v,a,a+b,t);
        }
        printf("Case %d: %d\n",kase++,bfs());
    }
    return 0;
}