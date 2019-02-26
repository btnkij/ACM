/**
* Number:p2762
* Title:太空飞行计划问题
* Status:AC
* Tag:[网络流最大流]
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

#define INF 0x7fffffff
#define PI acos(-1)
typedef long long ll;

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=100+10;
const int MAXM=MAXN*MAXN*2;
struct Edge
{
    int from,to,cap;
}edges[MAXM];
int tot,head[MAXN],nxt[MAXM];
void add1(int from,int to,int cap)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.cap=cap;
    nxt[tot]=head[from];
    head[from]=tot++;
}
void add2(int from,int to,int cap)
{
    // printf("%d %d %d\n",from,to,cap);
    add1(from,to,cap);
    add1(to,from,0);
}
int src,dst;
int dep[MAXN];
bool bfs()
{
    mset(dep,0);
    dep[src]=1;
    queue<int> Q;
    Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=nxt[i])
        {
            Edge& e=edges[i];
            if(!e.cap || dep[e.to])continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]!=0;
}
int cur[MAXN];
int dfs(int u,int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(!e.cap || dep[e.to]!=dep[u]+1)continue;
        int f=dfs(e.to, min(flow, e.cap));
        if(f)
        {
            e.cap-=f;
            edges[i^1].cap+=f;
            return f;
        }
    }
    return 0;
}
int dinic()
{
    int ans=0;
    while(bfs())
    {
        memcpy(cur,head,sizeof(cur));
        int f;
        while(f=dfs(src,INF))ans+=f;
    }
    return ans;
}

char tools[10000];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    int m,n; readi2(m,n);
    src=0, dst=105;
    int sum=0;
    rep(i,1,m)
    {
        int t; readi(t);
        sum+=t;
        add2(src,i,t);
        cin.getline(tools, 10000);
        int ulen = 0, tool;
        while (sscanf(tools + ulen, "%d", &tool) == 1)
        {
            add2(i,50+tool,INF);
            if (tool == 0)
                ulen++;
            else
            {
                while (tool)
                {
                    tool /= 10;
                    ulen++;
                }
            }
            ulen++;
        }
    }
    rep(i,1,n)
    {
        int t; readi(t);
        add2(50+i,dst,t);
    }
    int ans=sum-dinic();
    rep(i,1,m)
    {
        if(dep[i]>0)printf("%d ",i);
    }
    printf("\n");
    rep(i,1,n)
    {
        if(dep[50+i]>0)printf("%d ",i);
    }
    printf("\n%d",ans);
    return 0;
}