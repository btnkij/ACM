/**
* Number:ybt1330
* Title:最少步数
* Status:AC
* Tag:[bfs]
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

const int dir[][2]={{-2,-2},{-1,-2},{+1,-2},{+2,-2},{-2,-1},{+2,-1},{-2,+1},{+2,+1},{-2,+2},{-1,+2},{+1,+2},{+2,+2}};
bool vis[110][110];
struct HeapNode
{
    int x,y;
    int g;
};
int bfs(int x,int y)
{
    queue<HeapNode> Q;
    Q.push((HeapNode){x,y,0});
    while(!Q.empty())
    {
        HeapNode node=Q.front();
        Q.pop();
        // printf("# %d %d\n",node.x,node.y);
        if(node.x==1 && node.y==1)return node.g;
        if(vis[node.x][node.y])continue;
        vis[node.x][node.y]=true;
        for(int i=0;i<12;i++)
        {
            int xx=node.x+dir[i][0];
            int yy=node.y+dir[i][1];
            if(1<=xx && xx<=100 && 1<=yy && yy<=100 && !vis[xx][yy])
            {
                Q.push((HeapNode){xx,yy,node.g+1});
            }
        }
    }
    return INF;
}
int main()
{
    int x,y;
    while(scanf("%d %d",&x,&y)!=EOF)
    {
        memset(vis,false,sizeof(vis));
        int ans=bfs(x,y);
        printf("%d\n",ans);
    }
    return 0;
}