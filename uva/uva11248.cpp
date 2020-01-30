/**
* Number:uva11248
* Title:Frequency Hopping
* Status:AC
* Tag:[网络流, 最大流]
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

const int MAXN=110;
const int MAXM=40000;

struct Edge
{
    int from,to,flow,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int flow)
{
    edges[edgeid]=(Edge){from,to,flow,head[from]};
    head[from]=edgeid++;
}

int src,dst;
int dep[MAXN],cur[MAXN];
void addflow(int from,int to,int flow)
{
    addedge(from,to,flow);
    addedge(to,from,0);
}
bool getdep()
{
    clr(dep,0); dep[src]=1;
    queue<int> Q; Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.flow==0 || dep[e.to])continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]>0;
}
int augment(int u,int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(e.flow==0 || dep[u]+1!=dep[e.to])continue;
        int f=augment(e.to,min(flow,e.flow));
        if(f)
        {
            e.flow-=f, edges[i^1].flow+=f;
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
        memcpy(cur,head,sizeof(head));
        while(f=augment(src,INF))maxflow+=f;
    }
    return maxflow;
}

Edge residue[MAXM];
vector<int> cut;
vector<pair<int,int> > ans;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,k;
    int kase=1;
    while(readi(n,m,k)!=EOF && (n|m|k))
    {
        clr(head,-1); edgeid=0;
        rep(i,1,m)
        {
            int u,v,w; readi(u,v,w);
            addflow(u,v,w);
        }
        src=n+1, dst=n+2;
        addflow(src,1,k); addflow(n,dst,k);
        int maxflow=dinic();
        printf("Case %d: ",kase++);
        if(maxflow==k)
        {
            printf("possible\n");
            continue;
        }
        cut.clear();
        for(int i=0;i<edgeid;i+=2)
        {
            if(edges[i].flow==0)
            {
                cut.push_back(i);
            }
        }
        memcpy(residue,edges,sizeof(edges));
        ans.clear();
        for(int it:cut)
        {
            memcpy(edges,residue,sizeof(edges));
            edges[it].flow=k;
            if(maxflow+dinic()==k)ans.emplace_back(edges[it].from,edges[it].to);
        }
        if(ans.empty())
        {
            printf("not possible\n");
            continue;
        }
        sort(ans.begin(),ans.end());
        printf("possible option:");
        repne(i,0,ans.size())
        {
            printf("(%d,%d)%c",ans[i].first,ans[i].second,
                i==ans.size()-1?'\n':',');
        }
    }
    return 0;
}