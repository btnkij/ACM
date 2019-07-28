/**
* Number:2222
* Title:cxx仙女下凡
* Status:AC
* Tag:[dijkstra, k短路, 启发式搜索]
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

const int MAXN=1510;
const int MAXM=80010;
struct Edge
{
    int from,to,dis,nxt;
};
struct Graph
{
    Edge edges[MAXM];
    int head[MAXN],edge_id;
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
};

ll g[MAXN];
bool vis1[MAXN];
struct cmp1
{
    bool operator()(Node& lhs,Node& rhs)
    {
        return lhs.cost>rhs.cost;
    }
};
void dijkstra1(int src)
{
    priority_queue<Node, vector<Node>, cmp1> Q;
    Q.push((Node){src,0});
    while(!Q.empty())
    {
        Node cur=Q.top(); Q.pop();
        if(vis1[cur.pos])continue;
        vis1[cur.pos]=true;
        g[cur.pos]=cur.cost;
        for(int i=G1.head[cur.pos];~i;i=G1.edges[i].nxt)
        {
            Edge& e=G1.edges[i];
            if(vis1[e.to])continue;
            Q.push((Node){e.to,cur.cost+e.dis});
        }
    }
}

struct cmp2
{
    bool operator()(Node& lhs,Node& rhs)
    {
        return lhs.cost+g[lhs.pos]>rhs.cost+g[rhs.pos];
    }
};
int vis2[MAXN];
ll dijkstra2(int src,int dst,int k)
{
    priority_queue<Node, vector<Node>, cmp2> Q;
    Q.push((Node){src,0});
    while(!Q.empty())
    {
        Node cur=Q.top(); Q.pop();
        if(vis2[cur.pos]>=k)continue;
        vis2[cur.pos]++;
        if(cur.pos==dst && vis2[cur.pos]==k)return cur.cost;
        for(int i=G2.head[cur.pos];~i;i=G2.edges[i].nxt)
        {
            Edge& e=G2.edges[i];
            if(vis2[e.to]>=k)continue;
            Q.push((Node){e.to,cur.cost+e.dis});
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,k; readi(n,m,k);
    int s,t; readi(s,t);
    rep(i,1,n)G1.head[i]=G2.head[i]=-1;
    repne(i,0,m)
    {
        int u,v,w; readi(u,v,w);
        G2.addedge(u,v,w);
        G1.addedge(v,u,w);
    }
    dijkstra1(t);
    ll ans=dijkstra2(s,t,k);
    printf("%lld",ans);
    return 0;
}