/**
* Number:p3357
* Title:最长k可重线段集问题
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
    int from,to,cap;
    ll dis;
    int nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to,int cap,ll dis)
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
        int u=dst,flow=2333;
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

struct Segment
{
    ll x1,x2,len;
};
vector<Segment> segs;
vector<ll> id;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    int n,k; readi(n,k);
    repne(i,0,n)
    {
        ll x1,y1,x2,y2;
        scanf("%lld %lld %lld %lld",&x1,&y1,&x2,&y2);
        ll len=(ll)sqrt(pow(x1-x2,2)+pow(y1-y2,2));
        if(x1>x2)swap(x1,x2);
        x1<<=1, x2<<=1;
        if(x1==x2)x2++;
        else x1++;
        segs.push_back({x1,x2,len});
        id.push_back(x1); id.push_back(x2);
    }
    sort(id.begin(),id.end());
    id.erase(unique(id.begin(), id.end()), id.end());
    n=id.size();
    src=n+1, dst=src+1;
    repne(i,0,n)addedge(i,i+1,INF,0);
    for(auto it:segs)
    {
        int l=lower_bound(id.begin(), id.end(), it.x1)-id.begin()+1;
        int r=lower_bound(id.begin(), id.end(), it.x2)-id.begin()+1;
        addedge(l,r,1,-it.len);
    }
    addedge(src,1,k,0);
    addedge(n,dst,INF,0);
    printf("%lld",-mcmf());
    return 0;
}