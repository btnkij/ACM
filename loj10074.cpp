/**
* Number:loj10074
* Title:「一本通 3.2 例 3」架设电话线 
* Status:AC
* Tag:[dijkstra, 二分]
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
    int from, to, dis;
}edges[4010];
int head[1010], nxt[4010], tot;
void addEdge(int from, int to, int dis)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}

struct Node
{
    int pos, cost;
    bool operator<(const Node& rhs)const
    {
        return cost > rhs.cost;
    }
};
int n, p, k;
bool vis[1010];
bool dijkstra(int mid)
{
    fill(vis+1, vis+n+1, false);
    priority_queue<Node> Q;
    Q.push((Node){1, 0});
    while(!Q.empty())
    {
        Node nod=Q.top(); Q.pop();
        int u=nod.pos, c=nod.cost;
        if(u==n)return c<=k;
        if(vis[u])continue;
        vis[u]=true;
        for(int i=head[u];~i;i=nxt[i])
        {
            int v=edges[i].to;
            if(vis[v])continue;
            Q.push((Node){v, c+int(edges[i].dis>mid)});
        }
    }
    return false;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,p,k);
    fill(head+1,head+n+1,-1);
    while(p--)
    {
        int u,v,w; readi(u,v,w);
        addEdge(u,v,w); addEdge(v,u,w);
    }
    int lt=0, rt=INF;
    while(lt<rt)
    {
        int mid=(lt+rt)>>1;
        if(dijkstra(mid))rt=mid;
        else lt=mid+1;
    }
    if(lt==INF)printf("-1");
    else printf("%d",lt);
    return 0;
}