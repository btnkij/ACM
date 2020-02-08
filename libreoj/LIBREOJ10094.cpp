/**
* Number:loj10094
* Title:「一本通 3.5 练习 2」消息的传递
* Status:AC
* Tag:[tarjan]
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

const int MAXN=1010;
int adj[MAXN][MAXN];
int dfsid,dfn[MAXN],low[MAXN];
int grpid,grp[MAXN];
stack<int> trace;
int n;
void scc(int u)
{
    dfn[u]=low[u]=++dfsid;
    trace.push(u);
    for(int v=1;v<=n;v++)
    {
        if(!adj[u][v])continue;
        if(!dfn[v])scc(v),low[u]=min(low[u],low[v]);
        else if(!grp[v])low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        ++grpid;
        int t;
        do
        {
            t=trace.top(); trace.pop();
            grp[t]=grpid;
        }while(t!=u);
    }
}
int indeg[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n);
    rep2(i,1,n,j,1,n)readi(adj[i][j]);
    rep(i,1,n)if(!dfn[i])scc(i);
    rep2(i,1,n,j,1,n)
    {
        if(!adj[i][j] || grp[i]==grp[j])continue;
        indeg[grp[j]]++;
    }
    int ans=count(indeg+1,indeg+grpid+1,0);
    printf("%d",ans);
    return 0;
}