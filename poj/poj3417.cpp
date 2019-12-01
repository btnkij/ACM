/**
 * Number:poj3417
 * Title:Network 
 * Status:AC
 * Tag:[lca, 树形dp]
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

const int MAXN = 1e5 + 4;
const int LOGN = 17;

struct Edge
{
    int from, to;
    int next;
};
Edge edges[MAXN << 1];
int elen;
int head[MAXN];
void addEdge(int from, int to)
{
    Edge &e = edges[elen];
    e.from = from;
    e.to = to;
    e.next = head[e.from];
    head[e.from] = elen;
    elen++;
}

int fa[MAXN][LOGN];
int tin[MAXN], tout[MAXN];
int timer;
void DfsLca(int node, int pre)
{
    tin[node] = timer++;
    fa[node][0] = pre;
    for (int i = 1; i < LOGN; i++)
    {
        fa[node][i] = fa[fa[node][i - 1]][i - 1];
        if (fa[node][i] == 0)
            break;
    }
    for (int i = head[node]; ~i; i = edges[i].next)
    {
        Edge &e = edges[i];
        if (e.to == pre)
            continue;
        DfsLca(e.to, node);
    }
    tout[node] = timer++;
}
bool isAncestor(int f, int u)
{
    return f == 0 || (tin[f] <= tin[u] && tout[u] <= tout[f]);
}
int lca(int u, int v)
{
    // printf("enter u=%d v=%d\n",u,v);
    if (isAncestor(u, v))
        return u;
    while (true)
    {
        int i;
        for (i = 0; i < LOGN; i++)
            if (isAncestor(fa[u][i], v))
                break;
        if (i == 0)
            break;
        // printf("#\n");
        u = fa[u][i - 1];
        // printf("u=%d\n",u);
    }
    // printf("ret %d\n",fa[u][0]);
    return fa[u][0];
}

int dp[MAXN];
void dfs(int node, int pre)
{
    int &cnt = dp[node];
    for (int i = head[node]; ~i; i = edges[i].next)
    {
        Edge &e = edges[i];
        if (e.to == pre)
            continue;
        dfs(e.to, node);
        cnt += dp[e.to];
    }
}
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    elen = 0;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    timer = 0;
    DfsLca(1, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        dp[u]++;
        dp[v]++;
        dp[lca(u, v)] -= 2;
    }
    dfs(1, 0);
    ll ans = 0;
    for (int i = 2; i <= n; i++)
    {
        if (dp[i] == 0)
            ans += m;
        else if (dp[i] == 1)
            ans += 1;
    }
    printf("%lld\n", ans);
    return 0;
}