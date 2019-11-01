/**
* Number:poj3680
* Title:Intervals
* Status:AC
* Tag:[网络流, 最小费用最大流]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <map>
using namespace std;

#define INF 0x3f3f3f3f
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

const int MAXN=500;
const int MAXM=2000;

struct Edge
{
    int from,to,flow,dis,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int flow,int dis)
{
    edges[edgeid]=(Edge){from,to,flow,dis,head[from]};
    head[from]=edgeid++;
}
void addflow(int from,int to,int flow,int dis)
{
    addedge(from,to,flow,dis);
    addedge(to,from,0,-dis);
}

int src,dst;
int dis[MAXN],pre[MAXN],vis[MAXN];
bool augment()
{
    clr(dis,INF); dis[src]=0;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.flow==0 || dis[u]+e.dis>=dis[e.to])continue;
            dis[e.to]=dis[u]+e.dis;
            pre[e.to]=i;
            if(!vis[e.to])
            {
                Q.push(e.to);
                vis[e.to]=true;
            }
        }
    }
    return dis[dst]<INF;
}
int mcmf()
{
    int mincost=0;
    while(augment())
    {
        int f=INF;
        for(int u=dst;u!=src;u=edges[pre[u]].from)
        {
            f=min(f,edges[pre[u]].flow);
        }
        for(int u=dst;u!=src;u=edges[pre[u]].from)
        {
            edges[pre[u]].flow-=f;
            edges[pre[u]^1].flow+=f;
            mincost+=edges[pre[u]].dis;
        }
    }
    return mincost;
}

vector<int> id;
int a[210],b[210],w[210];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n,k; readi(n,k);
        id.clear();
        rep(i,1,n)
        {
            readi(a[i],b[i],w[i]);
            id.push_back(a[i]);
            id.push_back(b[i]);
        }
        sort(id.begin(),id.end());
        id.erase(unique(id.begin(),id.end()),id.end());
        src=id.size()+1, dst=id.size()+2;
        clr(head,-1); edgeid=0;
        addflow(src,1,k,0);
        addflow(id.size(),dst,k,0);
        repne(i,1,id.size())addflow(i,i+1,INF,0);
        rep(i,1,n)
        {
            int u=lower_bound(id.begin(),id.end(),a[i])-id.begin()+1;
            int v=lower_bound(id.begin(),id.end(),b[i])-id.begin()+1;
            addflow(u,v,1,-w[i]);
        }
        int ans=-mcmf();
        printf("%d\n",ans);
    }
    return 0;
}