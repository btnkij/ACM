/**
 * Number:uva1664
 * Title:Conquer a New Region
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

const int MAXN=200004;
int par[MAXN];
struct Node
{
    ll cost;
    int cnt;
}nodes[MAXN];
struct Edge
{
    int x,y,cost;
    Edge(int x,int y,int cost)
    {
        this->x=x;
        this->y=y;
        this->cost=cost;
    }
    bool operator<(const Edge& rhs)const
    {
        return this->cost > rhs.cost;
    }
};
vector<Edge> edges;
int n;
void init()
{
    edges.clear();
    for(int i=1;i<=n;i++)
    {
        par[i]=i;
        nodes[i].cost=0;
        nodes[i].cnt=1;
    }
}
int findRoot(int x)
{
    return x==par[x] ? x : par[x]=findRoot(par[x]);
}
bool merge(const Edge& ed)
{
    int rx=findRoot(ed.x);
    int ry=findRoot(ed.y);
    // if(rx==ry)return false;
    ll costx=nodes[rx].cost+ll(ed.cost)*nodes[ry].cnt;
    ll costy=nodes[ry].cost+ll(ed.cost)*nodes[rx].cnt;
    if(costx<costy)
    {
        swap(costx,costy);
        swap(rx,ry);
    }
    par[ry]=rx;
    nodes[rx].cost=costx;
    nodes[rx].cnt+=nodes[ry].cnt;
    return true;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        init();
        for(int i=1;i<n;i++)
        {
            int x,y,d;
            scanf("%d %d %d",&x,&y,&d);
            edges.emplace_back(x,y,d);
        }
        sort(edges.begin(),edges.end());
        for(Edge& it : edges)
        {
            merge(it);
        }
        cout<<(nodes[findRoot(1)].cost)<<endl;
    }
    return 0;
}