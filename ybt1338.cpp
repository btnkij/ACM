/**
* Number:ybt1338
* Title:医院设置
* Status:AC
* Tag:[树, dfs]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;

struct Edge
{
    int to;
    int next;
} edges[20010];
int cnte;
int head[104];
void add_edge(int from, int to)
{
    edges[cnte].to = to;
    edges[cnte].next = head[from];
    head[from] = cnte;
    cnte++;
}
int nodes[104];

int weight;
void dfs(int src, int dep, int pre)
{
    weight += nodes[src] * dep;
    for (int i = head[src]; ~i; i = edges[i].next)
    {
        if (edges[i].to == pre)
            continue;
        dfs(edges[i].to, dep + 1, src);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    memset(head, -1, sizeof(head));
    cnte = 0;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int w, l, r;
        scanf("%d %d %d", &w, &l, &r);
        nodes[i] = w;
        if (l)
        {
            add_edge(i, l);
            add_edge(l, i);
        }
        if (r)
        {
            add_edge(i, r);
            add_edge(r, i);
        }
    }
    int ans = INF;
    for (int i = 1; i <= n; i++)
    {
        weight = 0;
        dfs(i, 0, 0);
        ans = min(ans, weight);
    }
    printf("%d\n", ans);
    return 0;
}