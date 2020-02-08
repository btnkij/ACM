/**
* Number:p3386
* Title:【模板】二分图匹配
* Status:?
* Tag:[hungary, 匈牙利算法, 二分图最大匹配]
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
    int from, to, nxt;
}edges[2000010];
int head[2010], edge_id;
void addedge(int from, int to)
{
    edges[edge_id] = (Edge){from, to, head[from]};
    head[from] = edge_id++;
}

int match[2010];
bool vis[2010];
bool hungary(int u)
{
    for(int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if(vis[v])continue;
        vis[v] = true;
        if(!match[v] || hungary(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}
int maxmatch(int n, int m)
{
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        fill(vis + 1, vis + 1 + n + m, false);
        if(hungary(i))ans++;
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,e; readi(n,m,e);
    mset(head,-1);
    repne(i,0,e)
    {
        int u,v; readi(u,v);
        if(v>m || u>n)continue;
        addedge(u,n+v);
    }
    int ans=maxmatch(n,m);
    printf("%d",ans);
    return 0;
}