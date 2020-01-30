/**
 * Number:uva1078
 * Title:Steam Roller
 * Status:AC
 * Tag:[动态边权的dijkstra]
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

struct Node
{
    int x,y,dir,dist; //dir: 0 for stop, 1~4 for up,right,down,left
    Node(int x,int y,int dir,int dist)
    {
        this->x=x; this->y=y; this->dir=dir; this->dist=dist;
    }
    bool operator<(const Node& rhs)const
    {
        return this->dist > rhs.dist;
    }
};
int dir[5][2]={{0,0},{-1,0},{0,1},{1,0},{0,-1}};
int r1,r2,c1,c2;
bool vis[104][104][5];
int adj[104][104][5];
int bfs()
{
    priority_queue<Node> Q;
    Q.emplace(r1,c1,0,0);
    while(!Q.empty())
    {
        Node node=Q.top();
        Q.pop();
        if(vis[node.x][node.y][node.dir])continue;
        // printf("x=%d y=%d dir=%d dist=%d\n",node.x,node.y,node.dir,node.dist);
        if(node.x==r2 && node.y==c2 && node.dir==0)return node.dist;
        vis[node.x][node.y][node.dir]=true;
        int* edge=adj[node.x][node.y];
        for(int i=1;i<=4;i++)
        {
            // printf("adj[%d][%d][%d] = %d\n",node.x,node.y,i,adj[node.x][node.y][i]);
            if(edge[i]==0)continue;
            Node to=node;
            to.x+=dir[i][0]; to.y+=dir[i][1];
            if(node.dir==0)
            {
                if(vis[to.x][to.y][i])continue;
                to.dir=i;
                to.dist+=edge[i]<<1;
                Q.push(to);
                to.dir=0;
                Q.push(to);
            }
            else if(node.dir!=i)continue;
            else
            {
                to.dist+=edge[i];
                if(!vis[to.x][to.y][i])Q.push(to);
                to.dist+=edge[i];
                to.dir=0;
                if(!vis[to.x][to.y][0])Q.push(to);
            }
        }
    }
    return -1;
}

int main()
{
    int R,C,kase=1;
    while(scanf("%d%d%d%d%d%d",&R,&C,&r1,&c1,&r2,&c2)!=EOF && R && C)
    {
        memset(vis,0,sizeof(vis));
        memset(adj,0,sizeof(adj));
        r1--;c1--;r2--;c2--;
        int d;
        for(int j=1;j<C;j++)
        {
            scanf("%d",&d);
            adj[0][j-1][2]=adj[0][j][4]=d;
        }
        for(int i=1;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                scanf("%d",&d);
                adj[i][j][1]=adj[i-1][j][3]=d;
            }
            for(int j=1;j<C;j++)
            {
                scanf("%d",&d);
                adj[i][j-1][2]=adj[i][j][4]=d;
            }
        }
        int ans=bfs();
        if(ans==-1)printf("Case %d: Impossible\n",kase++);
        else printf("Case %d: %d\n",kase++,ans);
    }
    return 0;
}