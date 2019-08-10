/**
* Number:p2754
* Title:[CTSC1999]家园
* Status:AC
* Tag:[网络流, 最大流, 分层图]
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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=50000;
const int MAXM=5000000;
struct Edge
{
    int from,to,cap,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to,int cap)
{
    edges[edge_id]=(Edge){from,to,cap,head[from]};
    head[from]=edge_id++;
    edges[edge_id]=(Edge){to,from,0,head[to]};
    head[to]=edge_id++;
}

int dep[MAXN];
bool bfs(int src,int dst)
{
    clr(dep,0);
    dep[src]=1;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.cap<=0 || dep[e.to])continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]!=0;
}
int cur[MAXN];
int dfs(int u,int dst,int flow)
{
    if(u==dst)
    {
        return flow;
    }
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(dep[u]+1!=dep[e.to] || e.cap<=0)continue;
        int f=dfs(e.to,dst,min(e.cap,flow));
        if(f)
        {
            e.cap-=f;
            edges[i^1].cap+=f;
            return f;
        }
    }
    return 0;
}
int dinic(int src,int dst)
{
    int maxflow=0;
    while(bfs(src,dst))
    {
        memcpy(cur,head,sizeof(head));
        int f;
        while(f=dfs(src,dst,INF))
        {
            maxflow+=f;
        }
    }
    return maxflow;
}

int n,m,k;
int id(int t,int p)
{
    return n*t+p;
}

int fa[20];
int getfa(int x)
{
    return x==fa[x]?x:fa[x]=getfa(fa[x]);
}
void merge(int x,int y)
{
    int rx=getfa(x),ry=getfa(y);
    if(rx!=ry)fa[rx]=ry;
}

int h[40],r[40];
vector<int> s[40];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m,k);
    clr(head,-1);
    rep(i,0,n+1)fa[i]=i;
    rep(i,1,m)
    {
        readi(h[i],r[i]);
        repne(j,0,r[i])
        {
            int p; readi(p);
            p+=2;
            s[i].push_back(p);
            if(j)merge(s[i].front(),p);
        }
    }
    if(getfa(1)!=getfa(2))
    {
        printf("0");
        return 0;
    }
    n+=2;
    addedge(0,id(0,2),k);
    int maxflow=0;
    for(int t=1;;t++)
    {
        rep(i,1,n)addedge(id(t-1,i),id(t,i),INF);
        rep(i,1,m)
        {
            addedge(id(t-1, s[i][(t-1)%r[i]]), id(t, s[i][t%r[i]]), h[i]);
        }
        maxflow+=dinic(0,id(t,1));
        if(maxflow==k)
        {
            printf("%d",t);
            break;
        }
    }
    return 0;
}