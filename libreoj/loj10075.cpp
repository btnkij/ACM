/**
* Number:loj10075
* Title:「一本通 3.2 练习 1」农场派对
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

struct {
    struct Edge
    {
        int from,to;
        ll dist;
    }edges[200010];
    int head[1010],nxt[200010],tot;
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
    bool vis[1010];
    int dis[1010];
    void operator()(int src)
    {
        std::priority_queue<Node> Q;
        Q.push((Node){src, 0});
        while(!Q.empty())
        {
            Node node=Q.top(); Q.pop();
            if(vis[node.pos])continue;
            vis[node.pos]=true;
            dis[node.pos]=node.cost;
            for(int i=head[node.pos]; ~i; i=nxt[i])
            {
                Edge& e=edges[i];
                if(vis[e.to])continue;
                Q.push((Node){e.to, node.cost+e.dist});
            }
        }
    }
}dij1, dij2;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,x; readi(n,m,x);
    fill(dij1.head+1, dij1.head+n+1, -1);
    fill(dij2.head+1, dij2.head+n+1, -1);
    while(m--)
    {
        int u,v,w; readi(u,v,w);
        dij1.add_edge(u,v,w);
        dij2.add_edge(v,u,w);
    }
    dij1(x); dij2(x);
    int ans=-INF;
    rep(i,1,n)
    {
        ans=max(ans, dij1.dis[i]+dij2.dis[i]);
    }
    printf("%d", ans);
    return 0;
}