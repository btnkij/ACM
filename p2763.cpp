/**
* Number:p2763
* Title:试题库问题
* Status:AC
* Tag:[网络流最大流]
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

const int MAXN=1000+20+2+10;
const int MAXM=(1000*20+1000+20)*2+10;
struct directed_graph
{
    struct edge
    {
        int from, to;
        ll weight;
        bool operator<(const edge &rhs) const
        {
            return weight < rhs.weight;
        }
    } edges[MAXM];
    int head[MAXN], nxt[MAXM];
    int n_node; // 顶点数
    int n_edge; // 边数
    void clear(int n_node)
    {
        this->n_node = n_node;
        this->n_edge = 0;
        memset(head + 1, -1, sizeof(int) * n_node);
    }
    void add_edge(int from, int to, int weight)
    {
        edge &e = edges[n_edge];
        e.from = from;
        e.to = to;
        e.weight = weight;
        nxt[n_edge] = head[from];
        head[from] = n_edge++;
    }
}G;

struct dinic
{
    int src, dst;
    directed_graph *G;
    int dep[MAXN];
    int cur[MAXN];
    void add_edge(int from, int to, int flow)
    {
        G->add_edge(from, to, flow);
        G->add_edge(to, from, 0);
    }
    bool bfs()
    {
        queue<int> Q;
        memset(dep + 1, 0, sizeof(int) * G->n_node);
        dep[src] = 1;
        Q.push(src);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for (int i = G->head[u]; ~i; i = G->nxt[i])
            {
                directed_graph::edge &e = G->edges[i];
                if (dep[e.to] || e.weight <= 0)
                    continue;
                dep[e.to] = dep[u] + 1;
                Q.push(e.to);
            }
        }
        return dep[dst] > 0;
    }
    int dfs(int u, int flow)
    {
        if (u == dst)
            return flow;
        for (int &i = cur[u]; ~i; i = G->nxt[i])
        {
            directed_graph::edge &e = G->edges[i];
            if (dep[e.to] != dep[u] + 1 || e.weight <= 0)
                continue;
            int f = dfs(e.to, min(flow, e.weight));
            if (f)
            {
                e.weight -= f;
                G->edges[i ^ 1].weight += f;
                return f;
            }
        }
        return 0;
    }
    ll operator()(int src, int dst)
    {
        this->src = src;
        this->dst = dst;
        ll ans = 0;
        while (bfs())
        {
            memcpy(cur + 1, G->head + 1, sizeof(int) * G->n_node);
            int f;
            while (f = dfs(src, INF))
                ans += f;
        }
        return ans;
    }
}solver;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int k,n; readi2(k,n);
    int sum=0;
    // 1..k 类型 k+1..k+n 题目
    int src=k+n+1, dst=src+1;
    G.clear(k+n+4);
    solver.G=&G;
    rep(i,1,k)
    {
        int t; readi(t);
        solver.add_edge(src,i,t);
        sum+=t;
    }
    repne(i,k+1,src)
    {
        solver.add_edge(i,dst,1);
        int p; readi(p);
        while(p--)
        {
            int t; readi(t);
            solver.add_edge(t,i,1);
        }
    }
    if(solver(src,dst)!=sum)
        printf("No Solution!\n");
    else
    {
        rep(i,1,k)
        {
            printf("%d: ",i);
            for(int j=G.head[i];~j;j=G.nxt[j])
            {
                directed_graph::edge& e=G.edges[j];
                if(e.weight || !(k+1<=e.to&&e.to<=k+n))continue;
                printf("%d ",e.to-k);
            }
            putchar('\n');
        }
    }
    return 0;
}