/**
* Number:ybt1380
* Title:分糖果(candy)
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to;
    int dist;
}edges[5000010];
int head[100010],nxt[5000010],tot;
void add_edge(int from, int to, int dist)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dist=dist;
    nxt[tot]=head[from];
    head[from]=tot++;
}

struct Node
{
    int pos;
    int cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
bool vis[100010];
int dis[100010];
void dijkstra(int src)
{
    priority_queue<Node> Q;
    Q.push((Node){src, 0});
    dis[src]=0;
    while(!Q.empty())
    {
        Node node=Q.top(); Q.pop();
        if(vis[node.pos])continue;
        vis[node.pos]=true;
        for(int i=head[node.pos]; ~i; i=nxt[i])
        {
            Edge& e=edges[i];
            if(vis[e.to] || dis[node.pos]+e.dist >= dis[e.to])continue;
            dis[e.to]=dis[node.pos]+e.dist;
            Q.push((Node){e.to, dis[e.to]});
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,p,c; readi(n,p,c);
    int m; readi(m);
    rep(i,1,n)
    {
        head[i]=-1;
        dis[i]=INF;
    }
    repne(i,0,p)
    {
        int u,v; readi(u,v);
        add_edge(u,v,1); add_edge(v,u,1);
    }
    dijkstra(c);
    int ans=*max_element(dis+1,dis+n+1)+m+1;
    printf("%d",ans);
    return 0;
}