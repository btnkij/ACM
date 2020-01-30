/**
* Number:ybt1261
* Title:城市交通路网
* Status:AC
* Tag:[dijkstra]
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))

int n;
int dis[110];
int adj[110][110];
int pre[110];
bool vis[110];
struct Node
{
    int id, pre;
    int cost;
    bool operator<(const Node &rhs) const
    {
        return this->cost > rhs.cost;
    }
};
void dijkstra(int src)
{
    priority_queue<Node> Q;
    Q.push((Node){src, 0, 0});
    while (!Q.empty())
    {
        Node node = Q.top();
        Q.pop();
        if (vis[node.id])
            continue;
        vis[node.id] = true;
        pre[node.id] = node.pre;
        dis[node.id] = node.cost;
        for (int i = 1; i <= n; i++)
        {
            if (!adj[node.id][i] || vis[i])
                continue;
            Q.push((Node){i, node.id, node.cost + adj[node.id][i]});
        }
    }
}
void show_path(int id)
{
    if (pre[id])
        show_path(pre[id]);
    printf("%d ", id);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            readi(adj[i][j]);
        }
    }
    dijkstra(1);
    printf("minlong=%d\n", dis[n]);
    show_path(n);
    return 0;
}