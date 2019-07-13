/**
 * 
 * Tarjan
 * 
**/

#include <stack>
#include <algorithm>

const int MAXN=10010;
const int MAXM=50010;

struct Edge
{
    int from,to,nxt;
}edges[MAXM];
int head[MAXN],edge_id;
void addedge(int from,int to)
{
    edges[++edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id;
}

int ord[MAXN],low[MAXN],dfs_id;
int grp[MAXN],grp_id;
int rk[MAXN];
std::stack<int> trace;
void tarjan(int u)
{
    ord[u]=low[u]=++dfs_id;
    trace.push(u);
    for(int i=head[u];i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!ord[v])tarjan(v);
        if(!grp[v])low[u]=std::min(low[u],low[v]);
    }
    if(ord[u]==low[u])
    {
        ++grp_id;
        int tmp;
        do
        {
            tmp=trace.top(); trace.pop();
            grp[tmp]=grp_id;
            rk[grp_id]++;
        }while(tmp!=u);
    }
}