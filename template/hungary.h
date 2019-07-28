/**
 * 
 * Hungary 匈牙利算法
 * 
**/

#include <algorithm>

struct Edge
{
    int from, to, nxt;
}edges[2000010];
int head[2010], edge_id;
void addedge(int from, int to)
{
    edges[edge_id] = (Edge){from, to, head[from]};
    head[from] = edge_id++;
}

int match[2010];
bool vis[2010];
bool hungary(int u)
{
    for(int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if(vis[v])continue;
        vis[v] = true;
        if(!match[v] || hungary(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}
int maxmatch(int n, int m)
{
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        std::fill(vis + 1, vis + 1 + n + m, false);
        if(hungary(i))ans++;
    }
    return ans;
}