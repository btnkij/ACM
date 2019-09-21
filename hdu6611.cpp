#pragma GCC optimize(2)
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

struct Edge
{
    int from,to,cap,dis,nxt;
}edges[5000000];
int head[4010],edge_id;
void addedge(int from,int to,int cap,int dis)
{
    edges[edge_id]=(Edge){from,to,cap,dis,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,0,-dis,head[to]};
    head[to]=edge_id++;
}

int src,dst;
int dis[4010],pre[4010],h[4010];
struct HeapNode
{
    int pos,cost;
    bool operator<(const HeapNode& rhs)const
    {
        return cost>rhs.cost;
    }
};
// bool spfa()
// {
//     mset(dis,INF);
//     dis[src]=0;
//     queue<int> Q; 
//     Q.push(src);
//     while(!Q.empty())
//     {
//         int u=Q.front(); Q.pop();
//         vis[u]=false;
//         for(int i=head[u];~i;i=edges[i].nxt)
//         {
//             Edge& e=edges[i];
//             if(e.cap<=0 || dis[u]+e.dis>=dis[e.to])continue;
//             dis[e.to]=dis[u]+e.dis;
//             pre[e.to]=i;
//             if(!vis[e.to])
//             {
//                 vis[e.to]=true;
//                 Q.push(e.to);
//             }
//         }
//     }
//     return dis[dst]<INF;
// }
bool dijkstra()
{
    mset(dis,INF);
    dis[src]=0;
    priority_queue<HeapNode> Q;
    Q.push((HeapNode){src,0});
    while(!Q.empty())
    {
        HeapNode cur=Q.top(); Q.pop();
        if(dis[cur.pos]<cur.cost)continue;
        for(int i=head[cur.pos];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.cap<=0 || dis[cur.pos]+e.dis+h[cur.pos]-h[e.to]>=dis[e.to])continue;
            dis[e.to]=dis[cur.pos]+e.dis+h[cur.pos]-h[e.to];
            pre[e.to]=i;
            Q.push((HeapNode){e.to, dis[e.to]});
        }
    }
    rep(i,1,dst)h[i]+=dis[i];
    return dis[dst]!=INF;
}
int mcmf()
{
    mset(h,0);
    int mincost=0;
    while(dijkstra())
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

int arr[2010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        edge_id=0;
        mset(head,-1);
        int n,k; readi(n,k);
        src=2*n+1, dst=src+1;
        addedge(src,1,k,0);
        rep(i,1,n)
        {
            readi(arr[i]);
            addedge(i,n+i,1,-arr[i]);
            addedge(n+i,dst,1,0);
        }
        rep(i,2,n)
        {
            addedge(1,i,INF,0);
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<i;j++)
            {
                if(arr[j]<=arr[i])
                {
                    addedge(n+j,i,1,0);
                }
            }
        }
        printf("%d\n",-mcmf());
    }
    return 0;
}