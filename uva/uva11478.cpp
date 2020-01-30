/**
 * Number:uva11478
 * Title:Halum
 * Status:AC
 * Tag:[差分约束,spfa,二分]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int INF=1e6;
typedef long long ll;

struct Edge
{
    int from,to,dist;
};
vector<int> adj[504];
Edge edges0[2704],edges[2704]; int cnte;
int n,m;
void AddEdge(int u,int v,int dist)
{
    adj[u].push_back(cnte);
    edges0[cnte].from=u; edges0[cnte].to=v; edges0[cnte].dist=dist;
    cnte++;
}
bool inque[504];
int cntq[504];
int dist[504];
bool spfa()
{
    const int MAX_INQUE=sqrt(n)+1;
    queue<int> Q;
    for(int i=1;i<=n;i++)
    {
        Q.push(i);
        inque[i]=true;
        cntq[i]=1;
        dist[i]=0;
    }
    while(!Q.empty())
    {
        int node=Q.front();
        Q.pop();
        inque[node]=false;
        for(int i:adj[node])
        {
            Edge& e=edges[i];
            if(dist[node]+e.dist<dist[e.to])
            {
                dist[e.to]=dist[node]+e.dist;
                if(!inque[e.to])
                {
                    cntq[e.to]++;
                    if(cntq[e.to]>MAX_INQUE)return false;
                    Q.push(e.to);
                    inque[e.to]=true;
                }
            }
        }
    }
    return true;
}
bool judge(int ans)
{
    for(int i=0;i<m;i++)
    {
        edges[i].dist=edges0[i].dist-ans;
    }
    return spfa();
}
int main()
{
    while(scanf("%d %d",&n,&m)!=EOF)
    {
        cnte=0;
        int maxe=0;
        for(int i=1;i<=n;i++)
        {
            adj[i].clear();
        }
        for(int i=0;i<m;i++)
        {
            int u,v,dist;
            scanf("%d %d %d",&u,&v,&dist);
            AddEdge(u,v,dist);
            maxe=max(maxe,dist);
        }
        maxe++;
        memcpy(edges,edges0,sizeof(Edge)*cnte);
        int lt=0,rt=maxe,mid;
        while(lt<rt)
        {
            mid=(lt+rt+1)>>1;
            if(judge(mid))lt=mid;
            else rt=mid-1;
        }
        if(lt==maxe)printf("Infinite\n");
        else if(lt==0)printf("No Solution\n");
        else printf("%d\n",lt);
    }
    return 0;
}