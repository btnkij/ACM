/**
* Number:scu3335
* Title:Windy's Route
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to,dis;
}edges[200010];
int head[1010],nxt[200010],tot;
void add(int from,int to,int dis)
{
    Edge& e=edges[tot];
    e.from=from,e.to=to,e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int n,m,src,dst;
bool vis[1010][2];
int dis[1010][2];
struct Node
{
    int u,half,cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
int dijkstra()
{
    mset(vis,false);
    priority_queue<Node> Q;
    Q.push((Node){src,0,0});
    while(!Q.empty())
    {
        Node node = Q.top(); Q.pop();
        if(node.u==dst)return node.cost;
        if(vis[node.u][node.half])continue;
        vis[node.u][node.half]=true;
        dis[node.u][node.half]=node.cost;
        for(int i=head[node.u];~i;i=nxt[i])
        {
            Edge& e=edges[i];
            if(!vis[e.to][0])
            {
                Q.push((Node){e.to,node.half,node.cost+e.dis});
            }
            if(!vis[e.to][1] && !node.half)
            {
                Q.push((Node){e.to,1,node.cost+e.dis/2});
            }
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
    int T; readi(T);
    while(T--)
    {
        readi(n,m,src,dst);
        tot=0;
        rep(i,1,n)head[i]=-1;
        repne(i,0,m)
        {
            int u,v,w; readi(u,v,w);
            add(u,v,w);
        }
        int ans=dijkstra();
        printf("%d",ans);
        if(T)putchar('\n');
    }
    return 0;
}