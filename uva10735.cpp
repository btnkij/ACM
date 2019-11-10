/**
* Number:uva10735
* Title:Euler Circuit
* Status:AC
* Tag:[网络流, 最大流, 欧拉回路]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

const int MAXN=200;
const int MAXM=4000;

struct Edge
{
    int from,to,flow,nxt;
};
struct Graph
{
    Edge edges[MAXM];
    int head[MAXN],edgeid;
    void addedge(int from,int to,int flow)
    {
        edges[edgeid]=(Edge){from,to,flow,head[from]};
        head[from]=edgeid++;
    }
}G1,G2;

int src,dst,dep[MAXN],cur[MAXN];
void addflow(int from,int to,int flow)
{
    G2.addedge(from,to,flow);
    G2.addedge(to,from,0);
}
bool getdep()
{
    clr(dep,0); dep[src]=1;
    queue<int> Q; Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=G2.head[u];~i;i=G2.edges[i].nxt)
        {
            Edge& e=G2.edges[i];
            if(dep[e.to] || e.flow==0)continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst];
}
int augment(int u,int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=G2.edges[i].nxt)
    {
        Edge& e=G2.edges[i];
        if(e.flow==0 || dep[u]+1!=dep[e.to])continue;
        int f=augment(e.to,min(flow,e.flow));
        if(f)
        {
            e.flow-=f, G2.edges[i^1].flow+=f;
            return f;
        }
    }
    return 0;
}
int dinic()
{
    int maxflow=0,f;
    while(getdep())
    {
        memcpy(cur,G2.head,sizeof(G2.head));
        while(f=augment(src,INF))maxflow+=f;
    }
    return maxflow;
}

bool vis[MAXM];
vector<int> circuit;
void dfs(int u)
{
    for(int i=G1.head[u];~i;i=G1.edges[i].nxt)
    {
        if(vis[i])continue;
        vis[i]=true;
        int v=G1.edges[i].to;
        dfs(v);
    }
    circuit.push_back(u);
}

int outdeg[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    repne(kase,0,T)
    {
        int n,m; readi(n,m);
        clr(outdeg,0);
        clr(G1.head,-1); G1.edgeid=0;
        clr(G2.head,-1); G2.edgeid=0;
        rep(i,1,m)
        {
            int u,v; char d[2];
            scanf("%d %d %s",&u,&v,d);
            outdeg[u]++, outdeg[v]--;
            if(d[0]=='D')
                G1.addedge(u,v,0);
            else if(d[0]=='U')
                addflow(u,v,1);
        }
        int fullflow=0;
        src=n+1, dst=src+1;
        bool ok=true;
        rep(i,1,n)
        {
            if(outdeg[i]&1)
            {
                ok=false;
                break;
            }
            if(outdeg[i]>0)
            {
                fullflow+=outdeg[i]/2;
                addflow(src,i,outdeg[i]/2);
            }
            else if(outdeg[i]<0)
            {
                addflow(i,dst,(-outdeg[i])/2);
            }
        }
        if(ok && fullflow!=dinic())ok=false;
        if(kase)puts("");
        if(!ok)
        {
            puts("No euler circuit exist");
            continue;
        }
        for(int i=0;i<G2.edgeid;i+=2)
        {
            Edge& e=G2.edges[i];
            if(e.from==src || e.to==dst)continue;
            if(e.flow)G1.addedge(e.from,e.to,0);
            else G1.addedge(e.to,e.from,0);
        }
        clr(vis,false);
        circuit.clear();
        dfs(1);
        for(int i=circuit.size()-1;i>=0;i--)
            printf("%d%c",circuit[i],i==0?'\n':' ');
    }
    return 0;
}