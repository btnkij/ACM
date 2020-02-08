/**
* Number:p3358
* Title:最长k可重区间集问题
* Status:AC
* Tag:[网络流, 最小费用最大流]
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

const int MAXN=1010;
const int MAXM=4000;
struct Edge
{
    int from,to,cap,dis,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to,int cap,int dis)
{
    edges[edge_id]=(Edge){from,to,cap,dis,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,0,-dis,head[to]};
    head[to]=edge_id++;
}

int src,dst;
int dis[MAXN],pre[MAXN];
bool vis[MAXN];
bool spfa()
{
    mset(dis,INF);
    dis[src]=0;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.cap<=0 || dis[u]+e.dis>=dis[e.to])continue;
            dis[e.to]=dis[u]+e.dis;
            pre[e.to]=i;
            if(!vis[e.to])
            {
                vis[e.to]=true;
                Q.push(e.to);
            }
        }
    }
    return dis[dst]!=INF;
}
int mcmf()
{
    int mincost=0;
    while(spfa())
    {
        int u=dst,flow=INF;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            flow=min(flow,e.cap);
            u=e.from;
        }
        u=dst;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            mincost+=flow*e.dis;
            e.cap-=flow;
            edges[pre[u]^1].cap+=flow;
            u=e.from;
        }
    }
    return mincost;
}

typedef pair<int,int> seg;
vector<seg> segs;
vector<int> id;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    int n,k; readi(n,k);
    repne(i,0,n)
    {
        int l,r; readi(l,r);
        segs.emplace_back(l,r);
        id.push_back(l); id.push_back(r);
    }
    sort(id.begin(),id.end());
    id.erase(unique(id.begin(), id.end()), id.end());
    src=id.size(), dst=src+1;
    repne(i,1,src)addedge(i-1,i,INF,0);
    for(auto it:segs)
    {
        int l=distance(id.begin(), lower_bound(id.begin(), id.end(), it.first));
        int r=distance(id.begin(), lower_bound(id.begin(), id.end(), it.second));
        addedge(l, r, 1, -(it.second-it.first));
    }
    addedge(src,0,k,0);
    addedge(src-1,dst,INF,0);
    printf("%d",-mcmf());
    return 0;
}