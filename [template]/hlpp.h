/**
 * 
 * 网络流最大流 Highest Level Preflow Push
 * 
**/

#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef int ll;
#define INF 0x3f3f3f3f

struct directed_graph
{
    struct edge
    {
        int from, to;
        ll weight;
        bool operator<(const edge &rhs) const
        {
            return weight < rhs.weight;
        }
    } edges[240010];
    int nxt[240010];
    int head[1210];
    int n_node; // 顶点数
    int n_edge; // 边数
    void clear(int n_node)
    {
        this->n_node = n_node;
        this->n_edge = 0;
        memset(head + 1, -1, sizeof(int) * n_node);
    }
    void add_edge(int from, int to, ll weight)
    {
        edge &e = edges[n_edge];
        e.from = from;
        e.to = to;
        e.weight = weight;
        nxt[n_edge] = head[from];
        head[from] = n_edge++;
    }
};

struct hlpp
{
    struct Node
    {
        int id, height;
        ll flow;
    } nodes[1210];
    struct Comparer
    {
        bool operator()(const Node *lhs, const Node *rhs)
        {
            return lhs->height < rhs->height;
        }
    };
    int src, dst;
    directed_graph *G;
    int num[1210 << 1];
    bool vis[1210];
    priority_queue<Node *, vector<Node *>, Comparer> P;
    void add_edge(int from, int to, ll capacity)
    {
        if (capacity <= 0)
            return;
        G->add_edge(from, to, capacity);
        G->add_edge(to, from, 0);
    }
    bool bfs()
    {
        queue<int> Q;
        for (int i = 1; i <= G->n_node; i++)
        {
            nodes[i].id = i;
            nodes[i].flow = 0;
            nodes[i].height = INF;
        }
        nodes[dst].height = 0;
        Q.push(dst);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            int h = nodes[u].height + 1;
            for (int i = G->head[u]; ~i; i = G->nxt[i])
            {
                directed_graph::edge &e = G->edges[i ^ 1];
                if (nodes[e.from].height != INF || e.weight <= 0)
                    continue;
                nodes[e.from].height = h;
                Q.push(e.from);
            }
        }
        if (nodes[src].height == INF)
            return false;
        nodes[src].height = G->n_node;
        return true;
    }
    void discharge(int id)
    {
        for (int i = G->head[id]; ~i; i = G->nxt[i])
        {
            directed_graph::edge &e = G->edges[i];
            if (e.weight <= 0 || id != src && nodes[id].height != nodes[e.to].height + 1)
                continue;
            ll f = e.weight;
            if (id != src && f > nodes[id].flow)
                f = nodes[id].flow;
            e.weight -= f;
            G->edges[i ^ 1].weight += f;
            nodes[id].flow -= f;
            nodes[e.to].flow += f;
            if (!vis[e.to])
            {
                P.push(&nodes[e.to]);
                vis[e.to] = true;
            }
            if (id != src && nodes[id].flow <= 0)
                break;
        }
    }
    void relabel(int id)
    {
        int h = INF;
        for (int i = G->head[id]; ~i; i = G->nxt[i])
            if (G->edges[i].weight > 0)
            {
                h = min(h, nodes[G->edges[i].to].height);
            }
        nodes[id].height = h + 1;
    }
    ll operator()(int src, int dst)
    {
        this->src = src;
        this->dst = dst;
        if (!bfs())
            return 0;
        memset(vis + 1, false, sizeof(bool) * G->n_node);
        vis[src] = vis[dst] = true;
        memset(num, 0, sizeof(int) * (G->n_node << 1));
        for (int i = 1; i <= G->n_node; i++)
            if (nodes[i].height < INF)
                num[nodes[i].height]++;
        P = priority_queue<Node *, vector<Node *>, Comparer>();
        discharge(src);
        while (!P.empty())
        {
            Node *node = P.top();
            P.pop();
            vis[node->id] = false;
            discharge(node->id);
            if (node->flow > 0)
            {
                if (--num[node->height] == 0)
                {
                    for (int i = 1; i <= G->n_node; i++)
                    {
                        if (i == src || i == dst)
                            continue;
                        if (nodes[i].height >= node->height && nodes[i].height < G->n_node + 1)
                        {
                            nodes[i].height = G->n_node + 1;
                        }
                    }
                }
                relabel(node->id);
                num[node->height]++;
                P.push(node);
                vis[node->id] = true;
            }
        }
        return nodes[dst].flow;
    }
};