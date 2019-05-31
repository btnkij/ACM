/**
* Number:loj10083
* Title:「一本通 3.3 例 2」双调路径
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to;
    int c, t;
}edges[1000];
int head[110],nxt[1000],tot;
void add_edge(int from, int to, int c, int t)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.c=c, e.t=t;
    nxt[tot]=head[from];
    head[from]=tot++;
}

struct Node
{
    int pos, cost, t;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
int minc[110], mint[110];
int dis[110][30010];
bool vis[110][30010];
void dijkstra(int src)
{
    mset(minc,INF); mset(mint,INF);
    mset(dis,INF);
    std::priority_queue<Node> Q;
    Q.push((Node){src, 0, 0});
    while(!Q.empty())
    {
        Node node=Q.top(); Q.pop();
        int u=node.pos, t=node.t, c=node.cost;
        // printf("%d %d %d\n",u,c,t);
        if(vis[u][t])continue;
        dis[u][t]=c;
        minc[u]=min(minc[u],c);
        mint[u]=min(mint[u],t);
        vis[u][t]=true;
        for(int i=head[u]; ~i; i=nxt[i])
        {
            Edge& e=edges[i];
            int v=e.to, c1=c+e.c, t1=t+e.t;
            if(c1>=minc[v] && t1>=mint[v] || vis[v][t1])continue;
            Q.push((Node){v, c1, t1});
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,s,e; readi(n,m,s,e);
    mset(head,-1);
    while(m--)
    {
        int p,r,c,t; readi(p,r,c,t);
        add_edge(p,r,c,t); add_edge(r,p,c,t);
    }
    dijkstra(s);
    int pre=INF, ans=0;
    repne(i,0,30005)
    {
        if(dis[e][i]<pre)
        {
            ans++;
            pre=dis[e][i];
            // printf("%d %d\n",i,dis[e][i]);
        }
    }
    printf("%d",ans);
    return 0;
}