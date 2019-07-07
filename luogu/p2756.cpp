/**
* Number:p2756
* Title:飞行员配对方案问题
* Status:AC
* Tag:[二分图最大匹配]
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

#define INF 0x7fffffff
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

const int MAXN=210;
struct Edge
{
    int from,to,weight;
}edges[MAXN*MAXN];
int tot;
int nxt[MAXN*MAXN];
int head[MAXN];
int m,n;
void add_edge(int from,int to,int weight)
{
    edges[tot].from = from;
    edges[tot].to = to;
    edges[tot].weight = weight;
    nxt[tot]=head[from];
    head[from]=tot;
    tot++;
}

int src,dst;
int dep[MAXN];
bool bfs()
{
    memset(dep+1,0,sizeof(int)*(n+2));
    dep[src]=1;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        for(int i=head[u];~i;i=nxt[i])
        {
            int v=edges[i].to;
            if(edges[i].weight==0 || dep[v])continue;
            dep[v]=dep[u]+1;
            Q.push(v);
        }
    }
    return dep[dst]>0;
}

int cur[MAXN];
int dfs(int u, int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(!e.weight || dep[e.to]!=dep[u]+1)continue;
        int f=dfs(e.to, min(flow,e.weight));
        if(f)
        {
            e.weight -= f;
            edges[i ^ 1].weight += f;
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
        memcpy(cur + 1, head + 1, sizeof(int) * (n+2));
        int f;
        while(f=dfs(src,INF))ans+=f;
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(m,n);
    memset(head+1,-1,sizeof(int)*(n+2));
    int a,b;
    while(readi2(a,b)!=EOF && ~a && ~b)
    {
        add_edge(a,b,1); add_edge(b,a,0);
    }
    src=n+1; dst=n+2;
    rep(i,1,m)
    {
        add_edge(src, i, 1); add_edge(i, src, 0);
    }
    rep(i, m+1, n)
    {
        add_edge(i, dst, 1); add_edge(dst, i, 0);
    }
    int ans=dinic();
    if(ans)
    {
        printf("%d\n", ans);
        for (int i = 0; i < tot; i += 2)
        {
            Edge &e = edges[i];
            if (e.weight == 0 && 1 <= e.from && e.from <= m)
            {
                printf("%d %d\n", e.from, e.to);
            }
        }
    }
    else printf("No Solution!\n");
    return 0;
}