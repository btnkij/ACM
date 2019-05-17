/**
 * 
 * 点分治
 * 
**/

#define INF 0x3f3f3f3f

#include <algorithm>

struct Edge
{
    int from, to, dis;
}edges[20010];
int head[10010], nxt[20010], tot;
void addEdge(int from, int to, int dis)
{
    Edge& e = edges[tot];
    e.from = from, e.to = to, e.dis = dis;
    nxt[tot] = head[from];
    head[from] = tot++;
}

int root, sum;
int rk[10010], maxrk;
bool cg[10010];
void getcg(int u, int pre) // 求重心
{
    rk[u] = 1;
    int tmp = -INF;
    for(int i = head[u]; ~i; i = nxt[i])
    {
        int v = edges[i].to;
        if(v == pre || cg[v])continue;
        getcg(v, u);
        tmp = std::max(tmp, rk[v]);
        rk[u] += rk[v];
    }
    tmp = std::max(tmp, sum - rk[u]);
    if(tmp < maxrk)maxrk = tmp, root = u;
}

void solve(int u) // 以u为树根，分治求解
{
    cg[u]=true;

    // do something

    for(int i = head[u]; ~i; i = nxt[i])
    {
        int v = edges[i].to;
        if(cg[v])continue;
        maxrk = INF, sum = rk[v];
        getcg(v, 0);
        solve(root);
    }
}

int main()
{
    int n; // 节点个数

    // input

    maxrk = INF, sum = n;
    getcg(1, 0);
    solve(root);
    return 0;
}