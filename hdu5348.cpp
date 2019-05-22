/**
* Number:hdu5348
* Title:MZL's endless loop
* Status:AC
* Tag:[欧拉路径]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from, to;
    bool vis;
}edges[6000010];
int head[100010], nxt[6000010], tot, deg[100010];
void addEdge(int from, int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.vis=false;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int cur[100010];
queue<int> Q;
void dfs(int u)
{
    for(int& i=cur[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(e.vis || edges[i^1].vis)continue;
        e.vis=true;
        deg[e.from]--, deg[e.to]--;
        dfs(e.to);
        return;
    }
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
        int n,m; readi(n,m);
        while(!Q.empty())Q.pop();
        rep(i,1,n)head[i]=-1, deg[i]=0;
        tot=0;
        repne(i,0,m)
        {
            int u,v; readi(u,v);
            addEdge(u,v); addEdge(v,u);
            deg[u]++, deg[v]++;
        }
        copy(head, head+n+1, cur);
        repne(i,1,n)
        {
            if(deg[i]&1)Q.push(i);
        }
        while(!Q.empty())
        {
            int u=Q.front(); Q.pop();
            if(deg[u]&1)dfs(u);
        }
        rep(i,1,n)
        {
            if(deg[i])dfs(i);
        }
        for(int i=0;i<tot;i+=2)
        {
            if(edges[i].vis)printf("1\n");
            else printf("0\n");
        }
    }
    return 0;
}