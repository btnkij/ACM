/**
 * 
 * dijkstra
 * 
**/

#include <queue>

typedef long long ll;

struct Edge
{
    int from,to;
    ll dist;
}edges[800010];
int head[200010],nxt[800010],tot;
void add_edge(int from, int to, ll dist)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dist=dist;
    nxt[tot]=head[from];
    head[from]=tot++;
}

struct Node
{
    int pos;
    ll cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
bool vis[200010];
ll dijkstra(int src, int dst)
{
    std::priority_queue<Node> Q;
    Q.push((Node){src, 0});
    while(!Q.empty())
    {
        Node node=Q.top(); Q.pop();
        if(vis[node.pos])continue;
        if(node.pos == dst)return node.cost;
        vis[node.pos]=true;
        for(int i=head[node.pos]; ~i; i=nxt[i])
        {
            Edge& e=edges[i];
            if(vis[e.to])continue;
            Q.push((Node){e.to, node.cost+e.dist});
        }
    }
    return -1;
}