/**
* Number:loj10077
* Title:「一本通 3.2 练习 3」最短路计数
* Status:AC
* Tag:[bfs, 记忆化搜索]
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

const int MOD = 100003;

struct Edge
{
    int from, to;
};
struct Graph
{
    Edge edges[400010];
    int head[100010], nxt[400010], tot;
    void init(int n)
    {
        tot=0;
        fill(head, head+n+1, -1);
    }
    void addEdge(int from, int to)
    {
        Edge& e=edges[tot];
        e.from=from, e.to=to;
        nxt[tot]=head[from];
        head[from]=tot++;
    }
}G;
struct Node
{
    int pos, cost;
};
bool vis[100010];
int dis[100010];
void bfs(int src)
{
    queue<Node> Q;
    Q.push((Node){src, 0});
    vis[src]=true;
    while(!Q.empty())
    {
        int u=Q.front().pos;
        int c=Q.front().cost;
        Q.pop();
        dis[u]=c;
        for(int i=G.head[u]; ~i; i=G.nxt[i])
        {
            int v=G.edges[i].to;
            if(vis[v])continue;
            Q.push((Node){v, c+1});
            vis[v]=true;
        }
    }
}
bool vis1[100010];
int ans[100010];
int dfs(int u)
{
    if(vis1[u])return ans[u];
    int& r=ans[u];
    for(int i=G.head[u]; ~i; i=G.nxt[i])
    {
        int v=G.edges[i].to;
        if(dis[v]+1==dis[u])
        {
            r=(r+dfs(v))%MOD;
        }
    }
    vis1[u]=true;
    return r;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    G.init(n);
    while(m--)
    {
        int u,v; readi(u,v);
        if(u==v)continue;
        G.addEdge(u,v); G.addEdge(v,u);
    }
    bfs(1);
    ans[1]=1, vis[1]=true;
    rep(i,1,n)printf("%d\n", dfs(i));
    return 0;
}