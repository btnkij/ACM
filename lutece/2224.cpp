/**
* Number:2224
* Title:cxx承包鱼塘
* Status:AC
* Tag:[dijkstra]
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

const int MAXN = 10010;
const int MAXM = 200010*2;
struct Edge
{
    int from, to, dis, nxt;
}edges[MAXM];
int head[MAXN], edge_id;
void addedge(int from, int to, int dis)
{
    edges[edge_id] = (Edge){from, to, dis, head[from]};
    head[from] = edge_id++;
}

struct Node
{
    int pos,t;
    ll cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
int n,m,k,s,t;
bool vis[MAXN][24];
ll mindis[MAXN][24];
ll dijkstra()
{
    priority_queue<Node> Q;
    Q.push((Node){s,0,0});
    while(!Q.empty())
    {
        Node cur=Q.top(); Q.pop();
        if(vis[cur.pos][cur.t])continue;
        vis[cur.pos][cur.t]=true;
        if(cur.pos==t)return cur.cost;
        for(int i=head[cur.pos];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(!vis[e.to][cur.t])
                Q.push((Node){e.to, cur.t, cur.cost+e.dis});
            if(cur.t<k&&!vis[e.to][cur.t+1])
                Q.push((Node){e.to, cur.t+1, cur.cost});
        }
    }
    return -1;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m,k);
    readi(s,t);
    rep(i,1,n)head[i]=-1;
    repne(i,0,m)
    {
        int u,v,w; readi(u,v,w);
        addedge(u,v,w); addedge(v,u,w);
    }
    ll ans=dijkstra();
    printf("%lld",ans);
    return 0;
}