/**
* Number:sp913
* Title:QTREE2 - Query on a tree II
* Status:AC
* Tag:[LCA]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=10010;
struct Edge
{
    int from,to,dis,nxt;
}edges[MAXN<<1];
int head[MAXN],edgeid;
void addedge(int from,int to,int dis)
{
    edges[edgeid]={from,to,dis,head[from]};
    head[from]=edgeid++;
}

int tin[MAXN],tout[MAXN],dfsid;
int fa[MAXN][15],dis[MAXN],dep[MAXN];
void dfs(int u,int pre)
{
    tin[u]=++dfsid;
    fa[u][0]=pre, dep[u]=dep[pre]+1;
    for(int i=1;i<15;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(e.to==pre)continue;
        dis[e.to]=dis[u]+e.dis;
        dfs(e.to,u);
    }
    tout[u]=++dfsid;
}
bool isAncestor(int x,int y)
{
    return x==0 || tin[x]<=tin[y] && tout[y]<=tout[x];
}
int lca(int x,int y)
{
    if(isAncestor(x,y))return x;
    if(isAncestor(y,x))return y;
    for(int i=14;i>=0;i--)
        if(!isAncestor(fa[x][i],y))
            x=fa[x][i];
    return fa[x][0];
}

int getdis(int x,int y)
{
    return dis[x]+dis[y]-2*dis[lca(x,y)];
}
int kth(int x,int y,int k)
{
    int r=lca(x,y);
    if(dep[x]-dep[r]+1<k)
    {
        k=dep[x]+dep[y]-k-2*dep[r]+2;
        x=y;
    }
    k--;
    for(int i=14;i>=0;i--)
        if((k>>i)&1)
            x=fa[x][i];
    return x;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        clr(head,-1), edgeid=0;
        repne(i,1,n)
        {
            int u,v,w; readi(u,v,w);
            addedge(u,v,w), addedge(v,u,w);
        }
        dfsid=0;
        dfs(1,0);
        char op[8];
        while(reads(op)!=EOF && strcmp(op,"DONE")!=0)
        {
            if(strcmp(op,"DIST")==0)
            {
                int a,b; readi(a,b);
                printf("%d\n",getdis(a,b));
            }
            else if(strcmp(op,"KTH")==0)
            {
                int a,b,k; readi(a,b,k);
                printf("%d\n",kth(a,b,k));
            }
        }
    }
    return 0;
}