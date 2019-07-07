/**
* Number:2144
* Title:吞吐量
* Status:AC
* Tag:[lca, 倍增]
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

#define INF 0x7f7f7f7f
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

const int MAXN=1e5+10;
const int LOGN=18;
struct Edge
{
    int from,to,dis;
}edges[MAXN<<1];
int head[MAXN],nxt[MAXN<<1],tot;
void addedge(int from,int to,int dis)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}
int timer=0;
int tin[MAXN],tout[MAXN];
int fa[MAXN][LOGN],mindis[MAXN][LOGN];
void dfs(int u,int pre)
{
    tin[u]=timer++;
    fa[u][0]=pre;
    for(int i=1;i<LOGN;i++)
    {
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.to==pre)
        {
            mindis[u][0]=e.dis;
            for(int i=1;i<LOGN;i++)
            {
                mindis[u][i]=min(mindis[u][i-1], mindis[fa[u][i-1]][i-1]);
            }
            break;
        }
    }
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.to==pre)
        {
            continue;
        }
        dfs(e.to,u);
    }
    tout[u]=timer++;
}
bool isAncestor(int x,int y)
{
    return x==0 || tin[x]<=tin[y] && tout[y]<=tout[x];
}
int lca(int x,int y)
{
    if(isAncestor(x,y))return x;
    if(isAncestor(y,x))return y;
    for(int i=LOGN-1;i>=0;i--)
        if(!isAncestor(fa[x][i],y))
            x=fa[x][i];
    return fa[x][0];
}
int solve(int x,int y)
{
    int r=lca(x,y);
    int ans=INF;
    if(x!=r)
    {
        int tmp=x;
        for(int i=LOGN-1;i>=0;i--)
        {
            if(!isAncestor(fa[tmp][i],r))
            {
                ans=min(ans,mindis[tmp][i]);
                tmp=fa[tmp][i];
            }
        }
        ans=min(ans,mindis[tmp][0]);
    }
    if(y!=r)
    {
        int tmp=y;
        for(int i=LOGN-1;i>=0;i--)
        {
            if(!isAncestor(fa[tmp][i],r))
            {
                ans=min(ans,mindis[tmp][i]);
                tmp=fa[tmp][i];
            }
        }
        ans=min(ans,mindis[tmp][0]);
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    mset(mindis,INF);
    int n,q; readi(n,q);
    repne(i,1,n)
    {
        int u,v,w; readi(u,v,w);
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs(1,0);
    while(q--)
    {
        int u,v; readi(u,v);
        printf("%d\n",solve(u,v));
    }
    return 0;
}