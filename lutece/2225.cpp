/**
* Number:2225
* Title:cxx的压岁钱
* Status:AC
* Tag:[]
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

struct Edge
{
    int from,to,cap,nxt;
}edges[1000100];
int head[20100],edge_id;
void addedge(int from,int to,int cap)
{
    edges[edge_id]=(Edge){from,to,cap,head[from]};
    head[from]=edge_id++;
}

int n,m,src,dst;
int dep[20100];
bool bfs()
{
    fill(dep, dep+dst+1, 0);
    dep[src]=1;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(dep[e.to] || e.cap<=0)continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]!=0;
}
int cur[20100];
int dfs(int u,int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(dep[u]+1!=dep[e.to] || e.cap<=0)continue;
        int f=dfs(e.to, min(flow, e.cap));
        if(f)
        {
            e.cap-=f;
            edges[i^1].cap+=f;
            return f;
        }
    }
    return 0;
}
int dinic()
{
    int ans=0;
    while(bfs())
    {
        copy(head, head+dst+1, cur);
        int f;
        while(f=dfs(src,INF))
        {
            ans+=f;
        }
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    src=n+m+1, dst=src+1;
    fill(head, head+dst+1, -1);
    rep(i,1,m)
    {
        int t; readi(t);
        addedge(src,i,t); addedge(i,src,0);
    }
    int tot=0;
    rep(i,1,n)
    {
        int c,k; readi(c,k);
        int id=m+i;
        tot+=c;
        addedge(id,dst,c); addedge(dst,id,0);
        repne(j,0,k)
        {
            int t; readi(t);
            addedge(t,id,INF); addedge(id,t,0);
        }
    }
    int maxflow=dinic();
    printf("%d",tot-maxflow);
    return 0;
}