/**
* Number:L2-001
* Title:紧急救援
* Status:AC
* Tag:[dijkstra, dp]
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
typedef int ll;

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
    int from,to,dis,nxt;
}edges[510*510];
int head[510],tot;
void add_edge(int from,int to,int dis)
{
    Edge& e=edges[tot];
    e.from=from,e.to=to,e.dis=dis;
    e.nxt=head[from];
    head[from]=tot++;
}

struct HeapNode
{
    int u,cost;
    bool operator<(const HeapNode& rhs)const
    {
        return cost > rhs.cost;
    }
};
int cnt[510];
int mindis[510];
bool vis[510];
void dijkstra(int src)
{
    priority_queue<HeapNode> Q;
    Q.push((HeapNode){src,0});
    while(!Q.empty())
    {
        HeapNode node=Q.top(); Q.pop();
        if(cnt[node.u] && node.cost > mindis[node.u])continue;
        // printf("cnt %d %d\n",node.u,cnt[node.u]);
        cnt[node.u]++;
        mindis[node.u]=node.cost;
        for(int i=head[node.u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(vis[e.to])continue;
            Q.push((HeapNode){e.to, node.cost+e.dis});
            // printf("push %d %d\n",e.to,node.cost+e.dis);
        }
    }
}

int num[510];
int dp[510],pre[510];
void dfs(int u)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(mindis[u]+e.dis>mindis[e.to])continue;
        if(dp[u]+num[e.to]>dp[e.to])
        {
            dp[e.to]=dp[u]+num[e.to];
            pre[e.to]=u;
            dfs(e.to);
        }
    }
}
void showPath(int u)
{
    if(~pre[u])showPath(pre[u]);
    if(~pre[u])putchar(' ');
    printf("%d",u);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,src,dst;
    readi(n,m,src,dst);
    repne(i,0,n)
    {
        readi(num[i]);
        head[i]=-1;
    }
    repne(i,0,m)
    {
        int u,v,w; readi(u,v,w);
        add_edge(u,v,w); add_edge(v,u,w);
    }
    dijkstra(src);
    pre[src]=-1;
    dp[src]=num[src];
    dfs(src);
    printf("%d %d\n",cnt[dst],dp[dst]);
    showPath(dst);
    return 0;
}