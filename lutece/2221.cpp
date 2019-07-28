/**
* Number:2221
* Title:毁灭东湖计划
* Status:AC
* Tag:[网络流, 最大流]
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
    int from,to,flow,nxt;
}edges[20010];
int head[210],edge_id;
void addedge(int from,int to,int flow)
{
    edges[edge_id]=(Edge){from,to,flow,head[from]};
    head[from]=edge_id++;
}

int n,m;
int dep[210];
int vis[210];
bool bfs()
{
    dep[1]=vis[1]=1;
    rep(i,2,n)dep[i]=vis[i]=0;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(vis[e.to] || e.flow<=0)continue;
            vis[e.to]=1;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[n]>0;
}
int cur[210];
int dfs(int u,int flow)
{
    if(u==n)return flow;
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(e.flow<=0 || dep[e.from]+1!=dep[e.to])continue;
        int f=dfs(e.to,min(flow,e.flow));
        if(f)
        {
            e.flow-=f;
            edges[i^1].flow+=f;
            return f;
        }
    }
    return 0;
}
int dinic()
{
    int ans=0;
    while(bfs())
    {
        memcpy(cur,head,sizeof(head));
        int f;
        while(f=dfs(1,INF))
        {
            ans+=f;
        }
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    rep(i,1,n)head[i]=-1;
    repne(i,0,m)
    {
        int u,v,w; readi(u,v,w);
        addedge(u,v,w); addedge(v,u,0);
    }
    printf("%d",dinic());
    return 0;
}