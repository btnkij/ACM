/**
* Number:ybt1420
* Title:Dijkastra(II)
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

#define INF 0x3f3f3f3f3f3f3f3fLL
#define PI acos(-1)
typedef long long ll;

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

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
    priority_queue<Node> Q;
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi2(n,m);
    rep(i,1,n)head[i]=-1;
    rep(i,1,m)
    {
        int u,v,d; readi3(u,v,d);
        add_edge(u,v,d); add_edge(v,u,d);
    }
    ll ans=dijkstra(1,n);
    printf("%lld",ans);
    return 0;
}