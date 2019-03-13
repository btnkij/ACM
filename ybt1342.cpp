/**
* Number:ybt1342
* Title:【例4-1】最短路径问题
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to;
    double dist;
}edges[10010];
int head[110],nxt[10010],tot;
void add_edge(int from,int to,double dist)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dist=dist;
    nxt[tot]=head[from];
    head[from]=tot++;
}
int n,m;
int x[110],y[110];
double dist[110];
bool vis[110];
struct HeapNode
{
    int u;
    double cost;
    bool operator<(const HeapNode& rhs)const
    {
        return cost>rhs.cost;
    }
};
double dijkstra(int src, int dst)
{
    rep(i,1,n)dist[i]=1e100;
    priority_queue<HeapNode> P;
    HeapNode node;
    node.u=src, node.cost=dist[src]=0;
    P.push(node);
    while(!P.empty())
    {
        node=P.top(); P.pop();
        if(node.u==dst)return node.cost;
        vis[node.u]=true;
        for(int i=head[node.u];~i;i=nxt[i])
        {
            Edge& e=edges[i];
            if(vis[e.to] || dist[e.to]<=dist[node.u]+e.dist)continue;
            dist[e.to]=dist[node.u]+e.dist;
            HeapNode nxtnode;
            nxtnode.u=e.to;
            nxtnode.cost=dist[e.to];
            P.push(nxtnode);
        }
    }
    return dist[dst];
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    readi(n);
    rep(i,1,n)readi2(x[i],y[i]);
    readi(m);
    repne(i,0,m)
    {
        int u,v; readi2(u,v);
        double d=sqrt(pow(x[u]-x[v],2)+pow(y[u]-y[v],2));
        add_edge(u,v,d); add_edge(v,u,d);
    }
    int src,dst; readi2(src,dst);
    double ans=dijkstra(src,dst);
    printf("%.2lf",ans);
    return 0;
}