/**
* Number:uva1006
* Title:Fixed Partition Memory Management
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

struct Edge
{
    int from,to,flow,dis,nxt;
}edges[1000100];
int head[600],edgeid;
void addedge(int from,int to,int flow,int dis)
{
    edges[edgeid]=(Edge){from,to,flow,dis,head[from]};
    head[from]=edgeid++;
}
void addedge2(int from,int to,int flow,int dis)
{
    addedge(from,to,flow,dis);
    addedge(to,from,0,-dis);
}

int mindis[600],pre[600];
bool vis[600];
bool spfa(int src,int dst)
{
    clr(mindis,INF);
    queue<int> Q;
    Q.push(src);
    mindis[src]=0;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.flow<=0)continue;
            if(mindis[u]+e.dis<mindis[e.to])
            {
                mindis[e.to]=mindis[u]+e.dis;
                pre[e.to]=i;
                if(!vis[e.to])
                {
                    vis[e.to]=true;
                    Q.push(e.to);
                }
            }
        }
    }
    return mindis[dst]!=INF;
}
int mcmf(int src,int dst)
{
    int mincost=0;
    while(spfa(src,dst))
    {
        int f=INF;
        for(int u=dst;u!=src;u=edges[pre[u]].from)
            f=min(f,edges[pre[u]].flow);
        for(int u=dst;u!=src;u=edges[pre[u]].from)
        {
            edges[pre[u]].flow-=f;
            edges[pre[u]^1].flow+=f;
            mincost+=edges[pre[u]].dis*f;
        }
    }
    return mincost;
}

int sz[12];
struct Node
{
    int k,s[12],t[12];
}nodes[60];
int id[12][60];
int sum[12][60];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m,n,kase=1;
    while(readi(m,n)!=EOF && (m|n))
    {
        rep(i,1,m)readi(sz[i]);
        rep(i,1,n)
        {
            Node& nod=nodes[i];
            readi(nod.k);
            repne(j,0,nod.k)readi(nod.s[j],nod.t[j]);
        }
        int tot=n;
        int src=++tot,dst=++tot;
        rep2(i,1,m,j,1,n)id[i][j]=++tot;
        clr(head,-1); edgeid=0;
        rep(i,1,n)
        {
            addedge2(src,i,1,0);
            // printf("src %d %d %d\n",i,1,0);
            Node& nod=nodes[i];
            rep(j,1,m)
            {
                if(sz[j]<nod.s[0])continue;
                int t=nod.t[upper_bound(nod.s,nod.s+nod.k,sz[j])-nod.s-1];
                repne(k,0,nod.k)
                {
                    if(nod.s[k]>sz[j])break;
                    rep(l,1,n)
                    {
                        addedge2(i,id[j][l],1,t*l);
                        // printf("%d (%d, %d) %d %d\n",i,j,l,1,t*l);
                    }
                }
            }
        }
        rep2(i,1,m,j,1,n)
        {
            addedge2(id[i][j],dst,1,0);
            // printf("(%d, %d) dst 1 0\n");
        }
        printf("Case %d\n",kase++);
        printf("Average turnaround time = %.2lf\n",(double)mcmf(src,dst)/n);
        clr(sum,0);
        rep(i,1,n)
        {
            for(int j=head[i];~j;j=edges[j].nxt)
            {
                Edge& e=edges[j];
                if(e.to>=id[1][1] && !e.flow)
                {
                    int mem=(e.to-id[1][1])/n+1;
                    int ord=(e.to-id[1][1])%n+1;
                    sum[mem][ord]=e.dis/ord;
                    break;
                }
            }
        }
        rep(i,1,m)for(int j=n;j>=1;j--)sum[i][j]+=sum[i][j+1];
        rep(i,1,n)
        {
            for(int j=head[i];~j;j=edges[j].nxt)
            {
                Edge& e=edges[j];
                if(e.to>=id[1][1] && !e.flow)
                {
                    int mem=(e.to-id[1][1])/n+1;
                    int ord=(e.to-id[1][1])%n+1;
                    printf("Program %d runs in region %d from %d to %d\n",
                        i,mem,sum[mem][ord+1],sum[mem][ord]);
                    break;
                }
            }
        }
        puts("");
    }
    return 0;
}