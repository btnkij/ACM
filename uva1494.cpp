/**
 * Number:uva1494,uvalive5713
 * Title:Qin Shi Huang's National Road System
 * Status:AC
 * Tag:[mst]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

const int MAXN=1010;

struct Edge
{
    int from,to;
    double dist;
    Edge(int from,int to,double dist)
    {
        this->from=from;
        this->to=to;
        this->dist=dist;
    }
    bool operator<(const Edge& rhs)const
    {
        return this->dist > rhs.dist;
    }
};
int n;
vector<Edge> edges;
vector<int> adj[MAXN];
void AddEdge(int from,int to,double dist)
{
    adj[from].push_back(edges.size());
    edges.push_back(Edge(from,to,dist));
    adj[to].push_back(edges.size());
    edges.push_back(Edge(to,from,dist));
}

double maxedge[MAXN][MAXN];
bool vis[MAXN];
double mst;
void Prim()
{
    mst=0;
    memset(vis,false,sizeof(vis));
    memset(maxedge,0,sizeof(maxedge));
    priority_queue<Edge> Q;
    vis[1]=true;
    for(int it:adj[1])
    {
        Q.push(edges[it]);
    }
    int cnt=n-1;
    while(!Q.empty() && cnt>0)
    {
        Edge e=Q.top();
        Q.pop();
        if(vis[e.to])continue;
        for(int i=1;i<=n;i++)
        {
            if(vis[i])
            {
                maxedge[i][e.to]=maxedge[e.to][i]=max(e.dist,maxedge[e.from][i]);
            }
        }
        mst+=e.dist;
        vis[e.to]=true;
        cnt--;
        for(int it:adj[e.to])
        {
            if(vis[edges[it].to])continue;
            Q.push(edges[it]);
        }
    }
}

struct
{
    double x,y,p;
}nodes[MAXN];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        edges.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)adj[i].clear();
        for(int i=1;i<=n;i++)
        {
            int x,y,p;
            scanf("%lf %lf %lf",&nodes[i].x,&nodes[i].y,&nodes[i].p);
            for(int j=1;j<i;j++)
            {
                AddEdge(
                    i,j,
                    sqrt(double(nodes[i].x-nodes[j].x)*(nodes[i].x-nodes[j].x)
                        +double(nodes[i].y-nodes[j].y)*(nodes[i].y-nodes[j].y))
                    );
            }
        }
        Prim();
        double A,B;
        double ans=0;
        for(const Edge& e:edges)
        {
            A=nodes[e.from].p+nodes[e.to].p;
            B=mst-maxedge[e.from][e.to];
            ans=max(ans,A/B);
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}