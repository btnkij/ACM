/**
 * 
 * Hungary 匈牙利算法
 * 
**/

#include <cstdio>
#include <algorithm>

const int MAXN=2e3+10;
const int MAXM=2e6+10;

struct Edge
{
    int from,to,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int match[MAXN]; // 与u匹配的点是match[u]，match[u]=0表示未匹配
bool vis[MAXN]; // 是否是匈牙利树上的节点
// 増广
bool dfs(int u)
{
    vis[u]=true;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(vis[v])continue;
        vis[v]=true;
        if(!match[v] || dfs(match[v]))
        {
            match[u]=v, match[v]=u;
            return true;
        }
    }
    return false;
}
// 求最大匹配数
int maxmatch(int nx,int ny)
{
    int ans=0;
    std::fill_n(match,nx+ny+1,0);
    for(int i=1;i<=nx;i++)
    {
        std::fill_n(vis,nx+ny+1,false);
        ans+=dfs(i);
    }
    return ans;
}
// 输出最小点覆盖的点集
void mincover(int nx,int ny)
{
    std::fill_n(vis,nx+ny+1,false);
    for(int i=1;i<=nx;i++)if(!match[i])dfs(i);
    for(int i=1;i<=nx;i++)if(!vis[i])printf(" r%d",i);
    for(int i=1;i<=ny;i++)if(vis[nx+i])printf(" c%d",i);
}