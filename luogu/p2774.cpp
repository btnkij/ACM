/**
* Number:p2774
* Title:方格取数问题
* Status:AC
* Tag:[网络流, 最小割]
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
    int from,to,cap,nxt;
}edges[100010];
int head[10010],edge_id;
void addedge(int from,int to,int cap)
{
    edges[edge_id]=(Edge){from,to,cap,head[from]};
    head[from]=edge_id++;
}

int dir[][2]={{-1,0},{1,0},{0,-1},{0,1}};
int src,dst;
int mat[110][110];

int dep[10010];
bool bfs()
{
    mset(dep,0);
    queue<int> Q;
    Q.push(src);
    dep[src]=1;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(dep[e.to] || e.cap<=0)continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]>0;
}
int cur[10010];
int dfs(int u,int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(dep[u]+1!=dep[e.to] || e.cap<=0)continue;
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
        memcpy(cur,head,sizeof(head));
        int f;
        while(f=dfs(src,INF))
        {
            ans+=f;
        }
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    mset(head,-1);
    src=n*m+1, dst=src+1;
    int sum=0;
    rep2(i,1,n,j,1,m)
    {
        readi(mat[i][j]);
        sum+=mat[i][j];
        int id=(i-1)*m+j;
        if((i+j)&1)
        {
            addedge(src,id,mat[i][j]);
            addedge(id,src,0);
            repne(k,0,4)
            {
                int x=i+dir[k][0], y=j+dir[k][1];
                if(1<=x && x<=n && 1<=y && y<=m)
                {
                    int id1=(x-1)*m+y;
                    addedge(id,id1,INF);
                    addedge(id1,id,0);
                }
            }
        }
        else
        {
            addedge(id,dst,mat[i][j]);
            addedge(dst,id,0);
        }
    }
    int ans=sum-dinic();
    printf("%d",ans);
    return 0;
}