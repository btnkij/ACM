/**
 * Number:uva1151
 * Title:Buy or Build
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

struct Edge
{
    int from,to;
    int dist;
    bool operator<(const Edge& rhs)const
    {
        return this->dist<rhs.dist;
    }
};
vector<Edge> edges;
vector<Edge> mst;
int n;
int npart;
int par[1010];
void init()
{
    npart=n;
    for(int i=1;i<=n;i++)
    {
        par[i]=i;
    }
}
int findRoot(int x)
{
    return x==par[x] ? x : par[x]=findRoot(par[x]);
}
bool merge(int x,int y)
{
    int rx=findRoot(x);
    int ry=findRoot(y);
    if(rx==ry)return false;
    par[rx]=ry;
    npart--;
    return true;
}

vector<int> subnet[8];
struct{
    int x,y;
}pos[1010];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        edges.clear();
        mst.clear();
        int q;
        scanf("%d %d",&n,&q);
        for(int i=0;i<q;i++)
        {
            subnet[i].clear();
            int m,w;
            scanf("%d %d",&m,&w);
            subnet[i].push_back(w);
            while(m--)
            {
                scanf("%d",&w);
                subnet[i].push_back(w);
            }
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%d %d",&pos[i].x,&pos[i].y);
            for(int j=1;j<i;j++)
            {
                edges.push_back((Edge){i,j,
                    (pos[i].x-pos[j].x)*(pos[i].x-pos[j].x)+(pos[i].y-pos[j].y)*(pos[i].y-pos[j].y)});
            }
        }
        sort(edges.begin(),edges.end());
        init();
        int cost=0;
        for(auto ed:edges)
        {
            if(merge(ed.from,ed.to))
            {
                cost+=ed.dist;
                mst.push_back(ed);
            }
            if(npart==1)break;
        }
        
        int mincost=cost;
        int ALL=(1<<q)-1;
        for(int i=1;i<=ALL;i++)
        {
            init();
            cost=0;
            for(int k=0;k<q;k++)
            {
                if((i&(1<<k))==0)continue;
                cost+=subnet[k][0];
                for(int j=2;j<subnet[k].size();j++)
                {
                    merge(subnet[k][1],subnet[k][j]);
                }
            }
            // printf("cost1=%d\n",cost);
            for(auto ed:mst)
            {
                if(merge(ed.from,ed.to))
                {
                    cost+=ed.dist;
                    // printf("%d %d %d\n",ed.from,ed.to,ed.dist);
                }
                if(cost>=mincost)break;
                if(npart==1)break;
            }
            mincost=min(mincost,cost);
        }
        printf("%d\n",mincost);
        if(T)putchar('\n');
    }
    return 0;
}