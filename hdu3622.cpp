/**
* Number:hdu3622
* Title:Bomb Game
* Status:AC
* Tag:[2-sat, tarjan, 二分]
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

const int MAXN=210;
struct Point
{
    int x,y;
}pos[MAXN];
double adj[MAXN][MAXN];

struct Edge
{
    int from,to,nxt;
}edges[MAXN*MAXN];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int dfsid,dfn[MAXN],low[MAXN];
int grpid,grp[MAXN];
stack<int> trace;
void tarjan(int u)
{
    dfn[u]=low[u]=++dfsid;
    trace.push(u);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!dfn[v])tarjan(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
        grp[u]=++grpid;
        while(trace.top()!=u)grp[trace.top()]=grpid, trace.pop();
        trace.pop();
    }
}

bool check(int n,double mid)
{
    clr(head,-1);
    edgeid=0;
    repne2(i,0,n,j,0,i)
    {
        if(adj[i][j]<mid)
        {
            addedge(i,j^1);
            addedge(j,i^1);
        }
    }
    dfsid=grpid=0;
    clr(dfn,0);
    clr(grp,0);
    repne(i,0,n)if(!dfn[i])tarjan(i);
    for(int i=0;i<n;i+=2)
    {
        if(grp[i]==grp[i^1])return false;
    }
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        n<<=1;
        repne(i,0,n)readi(pos[i].x,pos[i].y);
        double lt=1e100,rt=-1e100;
        repne2(i,0,n,j,0,i)
        {
            adj[i][j]=sqrt(pow(pos[i].x-pos[j].x,2)+pow(pos[i].y-pos[j].y,2));
            lt=min(lt,adj[i][j]);
            rt=max(rt,adj[i][j]);
        }
        while(rt-lt>1e-4)
        {
            double mid=(lt+rt)/2;
            if(check(n,mid))lt=mid;
            else rt=mid;
        }
        printf("%.2lf\n",lt/2);
    }
    return 0;
}