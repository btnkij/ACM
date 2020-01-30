/**
* Number:ybt1344
* Title:【例4-4】最小花费
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

#define INF 1e100
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

const int MAXN=2010;
struct Edge
{
    int from,to;
    double dist;
}edges[2000110];
int head[MAXN],nxt[2000110],tot;
void add_edge(int from,int to,double dist)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dist=dist;
    nxt[tot]=head[from];
    head[from]=tot++;
}

struct Node
{
    int pos;
    double cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
bool vis[MAXN];
int src,dst;
double dist[MAXN];
double dijkstra()
{
    priority_queue<Node> Q;
    Q.push(Node{src,100});
    dist[src]=100;
    while(!Q.empty())
    {
        Node u=Q.top(); Q.pop();
        if(vis[u.pos])continue;
        vis[u.pos]=true;
        for(int i=head[u.pos];~i;i=nxt[i])
        {
            Edge& e=edges[i];
            if(vis[e.to])continue;
            if(dist[e.to]>u.cost*e.dist)
            {
                dist[e.to]=u.cost*e.dist;
                Q.push(Node{e.to, dist[e.to]});
            }
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
    int n,m; readi2(n,m);
    while(m--)
    {
        int x,y; readi2(x,y);
        double z; scanf("%lf",&z);
        double d=100.0/(100-z);
        add_edge(x,y,d); add_edge(y,x,d);
    }
    readi2(dst,src);
    rep(i,1,n)dist[i]=INF;
    double ans=dijkstra();
    printf("%.8lf",ans);
    return 0;
}