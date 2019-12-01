/**
* Number:loj10076
* Title:「一本通 3.2 练习 2」Roadblocks
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
typedef unsigned long long ull;

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
}edges[200010];
int head[5010],nxt[200010],tot;
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

int dis[5010][2];
void dijkstra(int src, int dst)
{
    mset(dis, INF);
    std::priority_queue<Node> Q;
    Q.push((Node){src, 0});
    while(!Q.empty())
    {
        Node node=Q.top(); Q.pop();
        int u=node.pos, c=node.cost;
        if(c>=dis[u][1])continue;
        if(dis[u][0]==INF)dis[u][0]=c;
        else if(c!=dis[u][0]) dis[u][1]=c;
        for(int i=head[node.pos]; ~i; i=nxt[i])
        {
            Edge& e=edges[i];
            if(c+e.dist>=dis[e.to][1])continue;
            Q.push((Node){e.to, node.cost+e.dist});
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,r; readi(n,r);
    fill(head+1, head+n+1, -1);
    while(r--)
    {
        int u,v,w; readi(u,v,w);
        add_edge(u,v,w); add_edge(v,u,w);
    }
    dijkstra(1,n);
    printf("%d", dis[n][1]);
    return 0;
}