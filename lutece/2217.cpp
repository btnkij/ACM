/**
* Number:2217
* Title:oydy的征途III
* Status:AC
* Tag:[生成树, lca, dijkstra]
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

const int MAXN=100010;
const int MAXM=210000;
const int LOGN=18;
struct Edge
{
    int from,to,dis,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
bool extra[MAXM];
void addedge(int from,int to,int dis)
{
    edges[edge_id]=(Edge){from,to,dis,head[from]};
    extra[edge_id]=false;
    head[from]=edge_id++;
}

int ufs[MAXN];
int findr(int x)
{
    return x==ufs[x]?x:ufs[x]=findr(ufs[x]);
}
bool merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx==ry)return false;
    ufs[rx]=ry;
    return true;
}

vector<int> ex;
void buildTree(int n)
{
    rep(i,1,n)ufs[i]=i;
    for(int i=0;i<edge_id;i+=2)
    {
        Edge& e=edges[i];
        if(!merge(e.from,e.to))
        {
            extra[i]=extra[i^1]=true;
            ex.push_back(e.from);
        }
    }
}

struct
{
    int tin[MAXN], tout[MAXN], timer;
    int fa[MAXN][LOGN];
    ll dis[MAXN];
    void dfs(int u, int pre)
    {
        tin[u] = timer++;
        fa[u][0] = pre;
        for(int i = 1; i < LOGN; i++)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for(int i = head[u]; ~i; i = edges[i].nxt)
        {
            if(extra[i])continue;
            int v = edges[i].to;
            if(v != pre)
            {
                dis[v] = dis[u] + edges[i].dis;
                dfs(v, u);
            }
        }
        tout[u] = timer++;
    }
    void init(int root)
    {
        memset(fa, 0, sizeof(fa));
        timer = 1;
        dis[root] = 0;
        dfs(root, 0);
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
    ll getdis(int x, int y)
    {
        int r = operator()(x, y);
        return dis[x] + dis[y] - 2 * dis[r];
    }
}lca;

struct Node
{
    int pos;
    ll cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
ll dis[34][MAXN];
bool vis[MAXN];
void dijkstra(int src, int id)
{
    mset(vis,false);
    std::priority_queue<Node> Q;
    Q.push((Node){src, 0});
    while(!Q.empty())
    {
        Node node=Q.top(); Q.pop();
        if(vis[node.pos])continue;
        vis[node.pos]=true;
        dis[id][node.pos]=node.cost;
        for(int i=head[node.pos]; ~i; i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(vis[e.to])continue;
            Q.push((Node){e.to, node.cost+e.dis});
        }
    }
}

ll query(int u,int v)
{
    ll ans=lca.getdis(u,v);
    for(int i=0;i<ex.size();i++)
        ans=min(ans, dis[i][u]+dis[i][v]);
    return ans;
}

int s[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    mset(head,-1);
    repne(i,0,m)
    {
        int u,v,w; readi(u,v,w);
        addedge(u,v,w); addedge(v,u,w);
    }
    buildTree(n);
    lca.init(1);
    for(int i=0;i<ex.size();i++)
    {
        dijkstra(ex[i],i);
    }
    int t; readi(t);
    s[0]=1;
    rep(i,1,t)readi(s[i]);
    ll ans=0;
    rep(i,1,t)
    {
        ans+=query(s[i-1],s[i]);
    }
    printf("%lld",ans);
    return 0;
}