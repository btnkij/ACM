/**
* Number:ybt1351
* Title:【例4-12】家谱树
* Status:AC
* Tag:[拓扑排序]
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
}edges[110*110];
int head[110],nxt[110*110],tot;
int deg[110];
void add_edge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
    deg[to]++;
}

bool vis[110];
int sorted[110],tail;
void top_sort(int u)
{
    for(int i=head[u]; ~i; i=nxt[i])
    {
        int v=edges[i].to;
        if(vis[v])continue;
        top_sort(v);
    }
    vis[u]=true;
    sorted[tail++]=u;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)head[i]=-1;
    rep(i,1,n)
    {
        int t;
        while(readi(t)!=EOF && t)
        {
            add_edge(i,t);
        }
    }
    rep(i,1,n)
    {
        if(deg[i]==0)top_sort(i);
    }
    for(int i=tail-1;i>=0;i--)printf("%d ",sorted[i]);
    return 0;
}