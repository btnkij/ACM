/**
* Number:p2770
* Title:航空路线问题
* Status:AC
* Tag:[网络流, 最小费用最大流]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <string>
#include <map>
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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=4000;
const int MAXM=500000;
struct Edge
{
    int from,to,cap,r,dis,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to,int cap,int dis)
{
    edges[edge_id]=(Edge){from,to,cap,cap,dis,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,cap,0,-dis,head[to]};
    head[to]=edge_id++;
}

int src,dst;
int dis[MAXN],pre[MAXN];
bool vis[MAXN];
bool spfa()
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
            if(e.r<=0 || dis[u]+e.dis>=dis[e.to])continue;
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
int mincost,maxflow;
int mcmf()
{
    mincost=maxflow=0;
    while(spfa())
    {
        int u=dst,f=INF;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            f=min(f,e.r);
            u=e.from;
        }
        maxflow+=f;
        u=dst;
        while(u!=src)
        {
            Edge& e=edges[pre[u]];
            e.r-=f;
            edges[pre[u]^1].r+=f;
            mincost+=e.dis*f;
            u=e.from;
        }
    }
    return mincost;
}

int n;
map<string,int> id;
string name[110];
vector<string> path;
void findpath(int u)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        if(i&1)continue;
        Edge& e=edges[i];
        if(e.cap==e.r)continue;
        e.r++;
        if(1<=e.from && e.from<=n && e.to==e.from+n)
            path.push_back(name[e.from]);
        findpath(e.to);
        return;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(0);
    clr(head,-1);
    int v; cin>>n>>v;
    rep(i,1,n)
    {
        cin>>name[i];
        id[name[i]]=i;
    }
    string city1,city2;
    rep(i,1,v)
    {
        cin>>city1>>city2;
        int x=id[city1],y=id[city2];
        if(x>y)swap(x,y);
        addedge(x+n,y,INF,0);
    }
    addedge(1,1+n,2,-1);
    addedge(n,n+n,2,-1);
    repne(i,2,n)
    {
        addedge(i,i+n,1,-1);
    }
    src=n*2+1, dst=n*2+2;
    addedge(src,1,2,0);
    addedge(n+n,dst,2,0);
    mcmf();
    if(maxflow!=2)
    {
        cout<<"No Solution!";
    }
    else
    {
        cout<<-mincost-2<<endl;
        findpath(src);
        for(auto it:path)cout<<it<<endl;
        path.clear();
        findpath(src);
        path.pop_back();
        reverse(path.begin(),path.end());
        for(auto it:path)cout<<it<<endl;
    }
    return 0;
}