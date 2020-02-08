/**
* Number:p1251
* Title:餐巾计划问题
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

#define INF 0x3f3f3f3f3f3f3f3fLL
#define PI acos(-1)
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=1e4+10;
const int MAXM=8e4+10;
struct Edge
{
    int from,to;
    ll cap,dis;
    int nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to,ll cap,ll dis)
{
    edges[edge_id]=(Edge){from,to,cap,dis,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,0,-dis,head[to]};
    head[to]=edge_id++;
}

int src,dst;
ll dis[MAXN];
int pre[MAXN];
bool vis[MAXN];
bool spfa()
{
    clr(dis,0x3f);
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
    return dis[dst]<INF;
}
ll mcmf()
{
    ll mincost=0;
    while(spfa())
    {
        int u=dst;
        ll flow=INF;
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

ll need[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(0);
    clr(head,-1);
    int n; cin>>n;
    src=2*n+1, dst=src+1;
    rep(i,1,n)cin>>need[i];
    int cost_new, day_fast, cost_fast, day_slow, cost_slow;
    cin>>cost_new>>day_fast>>cost_fast>>day_slow>>cost_slow;
    addedge(src,1,INF,cost_new);
    rep(i,1,n)
    {
        addedge(src,i+n,need[i],0);
        addedge(i,dst,need[i],0);
        if(i>1)addedge(i-1,i,INF,0);
        if(i+day_fast<=n)addedge(i+n,i+day_fast,INF,cost_fast);
        if(i+day_slow<=n)addedge(i+n,i+day_slow,INF,cost_slow);
    }
    cout<<mcmf();
    return 0;
}