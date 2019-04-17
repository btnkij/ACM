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
    int from,to,dis;
}edges[100010*2];
int head[50010],nxt[100010*2],ne;
void add_edge(int from,int to,int dis)
{
    Edge& e=edges[ne];
    e.from=from, e.to=to, e.dis=dis;
    nxt[ne]=head[from];
    head[from]=ne++;
}

int dis[50010];
bool vis[50010];
struct Node
{
    int u,cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
void dijkstra(int src)
{
    mset(vis,false);
    priority_queue<Node> Q;
    Q.push((Node){src,0});
    while(!Q.empty())
    {
        Node node=Q.top(); Q.pop();
        if(vis[node.u])continue;
        vis[node.u]=true;
        dis[node.u]=node.cost;
        for(int i=head[node.u];~i;i=nxt[i])
        {
            Edge& e=edges[i];
            if(vis[e.to])continue;
            Q.push((Node){e.to, node.cost+e.dis});
        }
    }
}

int adj[10][10];
int pos[10];
bool vis2[10];
int ans;
int dfs(int u,int cost)
{
    vis2[u]=true;
    bool flag=true;;
    rep(i,1,5)
    {
        if(vis2[i])continue;
        flag=false;
        dfs(i,cost+adj[u][i]);
    }
    if(flag)
    {
        ans=min(ans,cost);
    }
    vis2[u]=false;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)head[i]=-1;
    pos[0]=1;
    rep(i,1,5)readi(pos[i]);
    repne(i,0,m)
    {
        int u,v,w;
        readi(u,v,w);
        add_edge(u,v,w); add_edge(v,u,w);
    }
    rep(i,1,5)
    {
        dijkstra(pos[i]);
        adj[0][i]=adj[i][0]=dis[1];
        rep(j,1,5)
        {
            adj[i][j]=adj[j][i]=dis[pos[j]];
        }
    }
    ans=INF;
    dfs(0,0);
    printf("%d",ans);
    return 0;
}