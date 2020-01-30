/**
* Number:ybt1341
* Title:【例题】一笔画问题
* Status:AC
* Tag:[dfs]
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

const int MAXN=5e5;
struct Edge
{
    int from, to;
}edges[MAXN];
int head[MAXN],nxt[MAXN],tot;
int deg[MAXN];
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from;
    e.to=to;
    deg[from]++;
    nxt[tot]=head[from];
    head[from]=tot++;
}
int n,m;
bool vis[MAXN];
int dep,pre[MAXN];
bool dfs(int u)
{
    if(dep==m)
    {
        printf("%d",u);
        return true;
    }
    dep++;
    for(int i=head[u];~i;i=nxt[i])
    {
        if(vis[i])continue;
        vis[i]=vis[i^1]=true;
        if(dfs(edges[i].to))
        {
            printf(" %d",u);
            return true;
        }
        vis[i]=vis[i^1]=false;
    }
    dep--;
    return false;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(n,m);
    rep(i,1,n)head[i]=-1;
    tot=0;
    repne(i,0,m)
    {
        int u,v; readi2(u,v);
        add_edge(u,v); add_edge(v,u);
    }
    int src=1;
    rep(i,1,n)
    {
        if(deg[i]&1)
        {
            src=i;
            break;
        }
    }
    dfs(src);
    return 0;
}