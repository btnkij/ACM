/**
* Number:
* Title:
* Status:?
* Tag:[]
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

const int MAXN = 20;
const int MAXM = 20*20*2;

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
        memset(head, -1, sizeof(int) * n_node);
    }
    void add_edge(int from, int to, ll weight)
    {
        edge &e = edges[n_edge];
        e.from = from;
        e.to = to;
        e.weight = weight;
        nxt[n_edge] = head[from];
        head[from] = n_edge++;
    }
}G;

struct
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
            memcpy(cur, G->head, sizeof(int) * G->n_node);
            int f;
            while (f = dfs(src, INF))
                ans += f;
        }
        return ans;
    }
}dinic;

int arr[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    dinic.G = &G;
    rep(kase,1,T)
    {
        int n; readi(n);
        int sum=0;
        rep(i,1,n)
        {
            readi(arr[i]);
            sum+=arr[i];
        }
        G.clear(2*n+5);
        int src=0, dst=2*n+1;
        int ub=2*n;
        rep(i,1,n)
        {
            if(!arr[i])continue;
            rep(j,n+1,ub)dinic.add_edge(i,j,1);
        }
        rep(i,1,n)
        {
            dinic.add_edge(src,i,arr[i]);
            dinic.add_edge(n+i,dst,INF);
        }
        int maxflow=dinic(src,dst);
        printf("Case #%d: ",kase);
        if(maxflow!=sum)
        {
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
            int cnt=0;
            rep(i,1,n)
            {
                for(int j=G.head[i]; ~j; j=G.nxt[j])
                {
                    if(G.edges[j].to!=src && !G.edges[j].weight)cnt++;
                }
            }
            printf("%d\n",cnt);
            rep(i,1,n)
            {
                for(int j=G.head[i]; ~j; j=G.nxt[j])
                {
                    directed_graph::edge& e=G.edges[j];
                    if(e.to!=src && !e.weight)
                    {
                        printf("%d %d\n",e.from,e.to-n);
                    }
                }
            }
        }
        
    }
    return 0;
}