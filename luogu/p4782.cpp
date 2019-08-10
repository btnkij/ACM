/**
* Number:p4782
* Title:【模板】2-SAT 问题
* Status:AC
* Tag:[2-SAT]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to,nxt;
}edges[2000010];
int head[2000010],edge_id;
void addedge(int from,int to)
{
    edges[edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id++;
}

int dfn[2000010], dfs_id, low[2000010];
int color[2000010], color_id;
stack<int> trace;
void tarjan(int u)
{
    dfn[u]=low[u]=++dfs_id;
    trace.push(u);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!dfn[v])tarjan(v);
        if(!color[v])low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
        color_id++;
        int t;
        do
        {
            t=trace.top(); trace.pop();
            color[t]=color_id;
        }while(t!=u);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    int n,m; readi(n,m);
    repne(i,0,m)
    {
        int x,a,y,b; readi(x,a,y,b);
        addedge(x+n*(a^1), y+n*b);
        addedge(y+n*(b^1), x+n*a);
    }
    rep(i,1,n<<1)if(!dfn[i])tarjan(i);
    rep(i,1,n)
    {
        if(color[i]==color[i+n])
        {
            printf("IMPOSSIBLE");
            return 0;
        }
    }
    printf("POSSIBLE\n");
    rep(i,1,n)
    {
        if(color[i]>=color[i+n])printf("1 ");
        else printf("0 ");
    }
    return 0;
}