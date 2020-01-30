#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int INF=0x3f3f3f3f;

struct Point
{
    int x,y;
};

Point dir[]={{-2,-1},{-2,+1},{-1,-2},{-1,+2},{+1,-2},{+1,+2},{+2,-1},{+2,+1}};

char s1[4],s2[4];
Point src,dst;

struct QueueNode
{
    int x,y,step;
};
bool inQueue[8][8];
int bfs()
{
    memset(inQueue,false,sizeof(inQueue));
    queue<QueueNode> Q;
    Q.push((QueueNode{src.x,src.y,0}));
    inQueue[src.x][src.y]=true;
    while(!Q.empty())
    {
        auto curNode=Q.front();
        Q.pop();
        if(curNode.x==dst.x && curNode.y==dst.y)return curNode.step;
        for(int i=0;i<8;i++)
        {
            QueueNode node=curNode;
            node.x+=dir[i].x;
            node.y+=dir[i].y;
            node.step=curNode.step+1;
            if(!inQueue[node.x][node.y] && 0<=node.x && node.x<8 && 0<=node.y && node.y<8)
            {
                Q.push(node);
                inQueue[node.x][node.y]=true;
            }
        }
    }
    return INF;
}

int main()
{
    while(scanf("%s %s",s1,s2)!=EOF)
    {
        src.x=s1[0]-'a';
        src.y=s1[1]-'1';
        dst.x=s2[0]-'a';
        dst.y=s2[1]-'1';
        printf("To get from %s to %s takes %d knight moves.\n",s1,s2,bfs());
    }
    return 0;
}