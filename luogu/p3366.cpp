/**
* Number:p3366
* Title:【模板】最小生成树
* Status:AC
* Tag:[mst, 最小生成树]
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

const int MAXN = 5e3 + 10;
const int MAXM = 2e5 + 10;

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

struct union_find_set
{
    int fa[MAXN];
    void clear(int n)
    {
        for(int i = 1; i <= n; i++)
            fa[i] = i;
    }
    int find_root(int x)
    {
        return x == fa[x] ? x : fa[x] = find_root(fa[x]);
    }
    bool merge(int x, int y)
    {
        int rx = find_root(x), ry = find_root(y);
        if(rx == ry)return false;
        fa[rx] = ry;
        return true;
    }
};

struct kruskal
{
    union_find_set ufs;
    ll operator()(directed_graph* G)
    {
        sort(G->edges, G->edges + G->n_edge);
        ufs.clear(G->n_node);
        int cnt = G->n_node - 1;
        ll ans = 0;
        for(int i = 0; i < G->n_edge; i++)
        {
            directed_graph::edge& e = G->edges[i];
            if(ufs.merge(e.from, e.to))
            {
                ans += e.weight;
                cnt--;
                if(!cnt)return ans;
            }
        }
        return -1;
    }
}mst;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi2(n,m);
    G.clear(n);
    while(m--)
    {
        int u,v,w;
        readi3(u,v,w);
        G.add_edge(u,v,w);    
    }
    ll ans=mst(&G);
    if(~ans)printf("%d",ans);
    else printf("orz");
    return 0;
}