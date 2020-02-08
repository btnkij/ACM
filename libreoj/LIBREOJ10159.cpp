/**
* Number:loj10159
* Title:「一本通 5.2 练习 2」旅游规划 
* Status:AC
* Tag:[树型dp]
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
    int from,to;
}edges[200010*2];
int head[200010],nxt[200010*2],tot;
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int max1[200010],max2[200010],max3[200010];
void dfs1(int u,int pre)
{
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        dfs1(v, u);
        int t=max1[v]+1;
        if(t>max1[u])
        {
            max2[u]=max1[u];
            max1[u]=t;
        }
        else if(t>max2[u])
        {
            max2[u]=t;
        }
    }
}
void dfs2(int u,int pre)
{
    int cnt=0;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        if(max1[v]+1==max1[u])cnt++;
    }
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre)continue;
        if(max1[v]+1==max1[u] && cnt==1)
        {
            max3[v]=max(max3[u], max2[u])+1;
        }
        else
        {
            max3[v]=max(max3[u], max1[u])+1;
        }
        dfs2(v,u);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)head[i]=-1;
    repne(i,1,n)
    {
        int u,v; readi(u,v);
        add_edge(u,v); add_edge(v,u);
    }
    dfs1(0,-1);
    dfs2(0,-1);
    int d=0;
    repne(i,0,n)
        d=max(d,max1[i]+max(max2[i],max3[i]));
    repne(i,0,n)
        if(max1[i]+max(max2[i],max3[i])==d)printf("%d\n",i);
    return 0;
}