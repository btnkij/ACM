/**
* Number:loj10133
* Title:「一本通 4.4 例 4」次小生成树 
* Status:AC
* Tag:[lca, 严格次小生成树]
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

#define INF 0x3f3f3f3f3f3f3f3f
#define PI acos(-1)
typedef long long ll;

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

const int MAXN = 1e5 + 10;
const int MAXM = 6e5 + 10;
const int LOGN = 18;

struct directed_graph
{
    struct edge
    {
        int from, to;
        ll weight;
    } edges[MAXM];
    int head[MAXN], nxt[MAXM];
    int n_node; // 顶点数
    int n_edge; // 边数
    void clear(int n_node)
    {
        this->n_node = n_node;
        this->n_edge = 0;
        std::memset(head + 1, -1, sizeof(int) * n_node);
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
} G;

struct
{
    struct HeapNode
    {
        int eid;
        ll weight;
        bool operator<(const HeapNode& rhs)const
        {
            return weight > rhs.weight;
        }
    };
    bool vis[MAXN], tree[MAXM];
    ll operator()(directed_graph* G)
    {
        // memset(vis + 1, false, sizeof(bool) * G->n_node);
        // memset(tree, false, sizeof(bool) * G->n_edge);
        ll ans = 0;
        priority_queue<HeapNode> Q;
        vis[1] = true;
        int cnt = 1;
        for(int i = G->head[1]; ~i; i = G->nxt[i])
            Q.push((HeapNode){i, G->edges[i].weight});
        while(!Q.empty())
        {
            int eid = Q.top().eid;
            directed_graph::edge& e = G->edges[eid];
            Q.pop();
            if(vis[e.to])continue;
            vis[e.to] = true;
            tree[eid] = tree[eid ^ 1] = true;
            cnt++;
            ans += e.weight;
            for(int i = G->head[e.to]; ~i; i = G->nxt[i])
                if(!vis[G->edges[i].to])
                    Q.push((HeapNode){i, G->edges[i].weight});
        }
        return cnt == G->n_node ? ans : -1;
    }
}prim;

struct
{
    directed_graph* G;
    int tin[MAXN], tout[MAXN], timer;
    int fa[MAXN][LOGN]; // fa[i][j]: i的(1<<j)级祖先
    ll max1[MAXN][LOGN], max2[MAXN][LOGN]; // 最大边, 次大边
    void dfs(int u, int pre)
    {
        tin[u] = timer++;
        fa[u][0] = pre == -1 ? 0 : G->edges[pre].from;
        for(int i = 1; i < LOGN; i++)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        if(~pre)
        {
            max1[u][0] = G->edges[pre].weight;
            for(int i = 1; i < LOGN; i++)
            {
                ll t1 = max1[u][i - 1], t2 = max1[fa[u][i - 1]][i - 1];
                if(t1 < t2)swap(t1, t2);
                ll t3 = max(max2[u][i - 1], t2 = max2[fa[u][i - 1]][i - 1]);
                if(t3 > t1)t2 = t1, t1 = t3;
                else if(t1 > t3 && t3 > t2)t2 = t3;
                max1[u][i] = t1, max2[u][i] = t2;
            }
        }
        for(int i = G->head[u]; ~i; i = G->nxt[i])
        {
            if(!prim.tree[i])continue;
            int v = G->edges[i].to;
            if(v != G->edges[pre].from)
            {
                dfs(v, i);
            }
        }
        tout[u] = timer++;
    }
    void init(directed_graph* G, int root)
    {
        this->G = G;
        memset(fa, 0, sizeof(fa));
        memset(max1, 0xA0, sizeof(max1));
        memset(max2, 0xA0, sizeof(max2));
        timer = 1;
        dfs(root, -1);
    }
    bool isAncestor(int fa, int x)
    {
        return !fa || (tin[fa] <= tin[x] && tout[x] <= tout[fa]);
    }
    int operator()(int x, int y)
    {
        if(isAncestor(x, y))return x;
        if(isAncestor(y, x))return y;
        for(int i = LOGN - 1; i >= 0; i--)
            if(!isAncestor(fa[x][i], y))
                x = fa[x][i];
        return fa[x][0];
    }
    ll upperBound(int top, int x, ll weight)
    {
        // printf("top %d x %d w %lld\n",top,x,weight);
        ll t = -INF;
        for(int i = LOGN - 1; i >= 0; i--)
            if(!isAncestor(fa[x][i], top))
            {
                if(max1[x][i] < weight)t = max(t, max1[x][i]);
                if(max2[x][i] < weight)t = max(t, max2[x][i]);
                x = fa[x][i];
            }
        if(max1[x][0] < weight)t = max(t, max1[x][0]);
        if(max2[x][0] < weight)t = max(t, max2[x][0]);
        // printf("%lld\n",t);
        return t;
    }
}lca;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    G.clear(n);
    repne(i,0,m)
    {
        int u,v,w; readi(u,v,w);
        G.add_edge(u,v,w); G.add_edge(v,u,w);
    }
    ll sum=prim(&G);
    lca.init(&G, 1);
    ll ans=INF;
    for(int i=0;i<G.n_edge;i+=2)
    {
        if(prim.tree[i])continue;
        directed_graph::edge& e=G.edges[i];
        int r=lca(e.from, e.to);
        ll t=max(lca.upperBound(r,e.from,e.weight), lca.upperBound(r,e.to,e.weight));
        if(t==-INF)continue;
        ans=min(ans,sum-t+e.weight);
    }
    printf("%lld",ans);
    return 0;
}