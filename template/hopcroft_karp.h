/**
 * 
 * 二分图匹配 Hopcroft-Karp
 * 
**/

#include <algorithm>
#include <queue>

#define INF 0x3f3f3f3f
const int MAXN = 100010;
const int MAXM = 300010;

struct Edge
{
    int from, to, nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = (Edge){from, to, head[from]};
    head[from] = edgeid++;
}

int nx, ny, m; // 左支点数, 右支点数, 边数
int dep[MAXN], d;
int match[MAXN]; // i和谁匹配
bool vis[MAXN];
bool bfs()
{
    d = INF;
    std::queue<int> Q;
    std::fill_n(dep, nx + ny + 1, 0);
    for (int i = 1; i <= nx; i++)
    {
        if (!match[i])
        {
            dep[i] = 1;
            Q.push(i);
        }
    }
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if (dep[u] > d)
            break;
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].to;
            if (dep[v])
                continue;
            dep[v] = dep[u] + 1;
            if (!match[v])
                d = dep[v];
            else
            {
                dep[match[v]] = dep[v] + 1;
                Q.push(match[v]);
            }
        }
    }
    return d != INF;
}
int dfs(int u)
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (vis[v] || dep[u] + 1 != dep[v])
            continue;
        vis[v] = true;
        if (match[v] && dep[v] == d)
            continue;
        if (!match[v] || dfs(match[v]))
        {
            match[u] = v, match[v] = u;
            return 1;
        }
    }
    return 0;
}
int hopcroft_karp() // 返回最大匹配数
{
    int ans = 0;
    while (bfs())
    {
        std::fill_n(vis, nx + ny + 1, false);
        for (int i = 1; i <= nx; i++)
        {
            if (!match[i])
                ans += dfs(i);
        }
    }
    return ans;
}