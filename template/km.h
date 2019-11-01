/**
 * 
 * KM 二分图完美匹配
 * 
**/

#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

const int MAXN=510;

int n,adj[MAXN][MAXN];
bool visx[MAXN],visy[MAXN];
int lx[MAXN],ly[MAXN];
int lef[MAXN];
bool dfs(int u)
{
    visx[u]=true;
    for(int v=1;v<=n;v++)
    {
        if(visy[v] || lx[u]+ly[v]!=adj[u][v])continue;
        visy[v]=true;
        if(!lef[v] || dfs(lef[v]))
        {
            lef[v]=u;
            return true;
        }
    }
    return false;
}
void update()
{
    int delta=INF;
    for(int i=1;i<=n;i++)if(visx[i])
        for(int j=1;j<=n;j++)if(!visy[j])
            delta=std::min(delta,lx[i]+ly[j]-adj[i][j]);
    for(int i=1;i<=n;i++)
    {
        if(visx[i])lx[i]-=delta;
        if(visy[i])ly[i]+=delta;
    }
}
int km()
{
    memset(lef,0,sizeof(lef)); memset(ly,0,sizeof(ly));
    for(int i=1;i<=n;i++)lx[i]=*std::max_element(adj[i]+1,adj[i]+n+1);
    for(int i=1;i<=n;i++)
    {
        while(true)
        {
            memset(visx,0,sizeof(visx)); memset(visy,0,sizeof(visy));
            if(dfs(i))break;
            else update();
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)ans+=lx[i]+ly[i];
    return ans;
}