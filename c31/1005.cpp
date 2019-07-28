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
    int from,to,dis,nxt;
};
struct Graph
{
    Edge edges[20010];
    int head[10010],edge_id;
    void addedge(int from,int to,int dis)
    {
        edges[edge_id]=(Edge){from,to,dis,head[from]};
        head[from]=edge_id++;
    }
}G1,G2;

struct Node
{
    int pos;
    ll cost;
    bool operator<(const Node& rhs)const
    {
        return cost>rhs.cost;
    }
};
ll mindis[10010];
void dijkstra()
{
    priority_queue<Node> Q;
    Q.push((Node){1,0});
    while(!Q.empty())
    {
        int u=Q.top().pos;
        ll c=Q.top().cost;
        Q.pop();
        if(mindis[u]!=INF)continue;
        mindis[u]=c;
        for(int i=G1.head[u];~i;i=G1.edges[i].nxt)
        {
            Edge& e=G1.edges[i];
            if(mindis[e.to]!=INF)continue;
            Q.push((Node){e.to,c+e.dis});
        }
    }
}

int dep[10010],cur[10010];
bool inque[10010];
bool bfs(int n)
{
    queue<int> Q;
    Q.push(1);
    rep(i,2,n)dep[i]=0;
    dep[1]=1;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        inque[u]=false;
        for(int i=G2.head[u];~i;i=G2.edges[i].nxt)
        {
            Edge& e=G2.edges[i];
            if(e.dis<=0 || dep[e.to])continue;
            dep[e.to]=dep[u]+1;
            if(!inque[e.to])
            {
                Q.push(e.to);
                inque[e.to]=true;
            }
        }
    }
    return dep[n]!=0;
}
int dfs(int u,int flow,int n)
{
    if(u==n)return flow;
    for(int& i=cur[u];~i;i=G2.edges[i].nxt)
    {
        Edge& e=G2.edges[i];
        if(e.dis<=0 || dep[u]+1!=dep[e.to])continue;
        int f=dfs(e.to,min(flow,e.dis),n);
        if(f>0)
        {
            e.dis-=f;
            G2.edges[i^1].dis+=f;
            return f;
        }
    }
    return 0;
}
ll dinic(int n)
{
    ll ans=0;
    while(bfs(n))
    {
        copy(G2.head+1,G2.head+1+n,cur+1);
        int f;
        while(f=dfs(1,INF,n))
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
    int T; readi(T);
    while(T--)
    {
        int n,m; readi(n,m);
        rep(i,1,n)
        {
            G1.head[i]=G2.head[i]=-1;
            mindis[i]=INF;
        }
        G1.edge_id=G2.edge_id=0;
        repne(i,0,m)
        {
            int x,y,c; readi(x,y,c);
            G1.addedge(x,y,c);
        }
        dijkstra();
        if(n==1 || mindis[n]==INF)
        {
            printf("0\n");
            continue;
        }
        repne(i,0,G1.edge_id)
        {
            Edge& e=G1.edges[i];
            if(mindis[e.from]+e.dis==mindis[e.to])
            {
                G2.addedge(e.from,e.to,e.dis);
                G2.addedge(e.to,e.from,0);
            }
        }
        ll ans=dinic(n);
        printf("%lld\n",ans);
    }
    return 0;
}