/**
 * 
 * SPFA 单源最短路, 判负环
 * 
**/

#include <cstring>
#include <queue>

#define INF 0x3f3f3f3f
typedef int ll;

struct directed_graph
{
    struct edge
    {
        int from, to;
        ll weight;
        int nxt;
        bool operator<(const edge &rhs) const
        {
            return weight < rhs.weight;
        }
    } edges[6010];
    int head[2010];
    int n_node; // 顶点数
    int n_edge; // 边数
    void clear(int n_node)
    {
        this->n_node = n_node;
        this->n_edge = 0;
        memset(head + 1, -1, sizeof(int) * n_node);
    }
    void add_edge(int from, int to, int weight)
    {
        edge &e = edges[n_edge];
        e.from = from;
        e.to = to;
        e.weight = weight;
        e.nxt = head[from];
        head[from] = n_edge++;
    }
};

struct spfa
{
    directed_graph *G;
    ll dis[2010];
    bool vis[2010];
    int cnt[2010];
    bool operator()(int src)
    {
        memset(dis + 1, INF, sizeof(ll) * G->n_node);
        memset(vis + 1, false, sizeof(bool) * G->n_node);
        memset(cnt + 1, 0, sizeof(int) * G->n_node);
        dis[src] = 0;
        std::queue<int> Q;
        Q.push(src);
        vis[src] = true;
        cnt[src] = 1;
        while (!Q.empty())
        {
            int cur = Q.front();
            Q.pop();
            vis[cur] = false;
            for (int i = G->head[cur]; ~i; i = G->edges[i].nxt)
            {
                directed_graph::edge &e = G->edges[i];
                if (dis[cur] + e.weight < dis[e.to])
                {
                    dis[e.to] = dis[cur] + e.weight;
                    if (!vis[e.to])
                    {
                        if (++cnt[e.to] >= G->n_node)
                            return false; // 存在负环
                        vis[e.to] = true;
                        Q.push(e.to);
                    }
                }
            }
        }
        return true; // 求出最短路
    }
};

/**
 * 
 * SPFA dfs优化 判负环
 * 
**/
#include <algorithm>

struct Edge
{
    int from,to;
    int dis;
}edges[6000];
int head[510], nxt[6000], tot;
void addEdge(int from, int to, int dis)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int dis[510];
bool vis[510];
bool spfa(int u)
{
    vis[u]=true;
    bool ans=false;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        int c=edges[i].dis;
        if(dis[u]+c<dis[v])
        {
            dis[v]=dis[u]+c;
            if(vis[v] || spfa(v))
            {
                ans=true;
                break;
            }
        }
    }
    vis[u]=false;
    return ans;
}

int n; // 节点数
bool check()
{
    std::fill(vis, vis+n+1, false);
    std::fill(dis, dis+n+1, 0);
    for(int i=1;i<=n;i++)if(spfa(i))return true;
    return false;
}