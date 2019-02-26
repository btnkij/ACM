/**
* Number:p3254
* Title:圆桌问题
* Status:AC
* Tag:[网络流最大流, dinic]
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

const int MAXN=150+270+10;
const int MAXM=(150*270+150+270)*2+10;
int n, m;
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
bool vis[280][160];
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
            if(e.to<n)vis[e.to][e.from-n]=true;
            else if(e.from<n)vis[e.from][e.to-n]=false;
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(head,-1);
    readi2(m,n);
    // 0..n-1 餐桌 n..n+m-1 单位
    src=n+m, dst=src+1;
    int sum=0;
    repne(i,0,m)
    {
        int t; readi(t);
        add2(src,n+i,t);
        sum+=t;
    }
    repne(i,0,n)
    {
        int t; readi(t);
        add2(i,dst,t);
    }
    repne2(i,n,src,j,0,n)add2(i,j,1);
    if(dinic()!=sum)printf("0");
    else
    {
        printf("1\n");
        repne(i,0,m)
        {
            repne(j,0,n)
            {
                if(vis[j][i])
                    printf("%d ",j+1);
            }
            putchar('\n');
        }
    }
    return 0;
}