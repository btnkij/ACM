/**
* Number:scu4439
* Title:Vertex Cover
* Status:AC
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
    int from, to;
}edges[2510];
int head[510], nxt[2510], tot;
void addEdge(int from, int to)
{
    Edge& e = edges[tot];
    e.from = from, e.to = to;
    nxt[tot] = head[from];
    head[from] = tot++;
}

int match[510];
bool vis[510];
bool augment(int u)
{
    for(int i = head[u]; ~i; i = nxt[i])
    {
        int v = edges[i].to;
        if(vis[v])continue;
        vis[v] = true;
        if(match[v] == -1 || augment(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}
int hungary(int n)
{
    int ans = 0;
    fill_n(match, n + 1, -1);
    for(int i = 1; i <= n; i++)
    {
        fill_n(vis, n + 1, false);
        ans += augment(i);
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    while(readi(n,m)!=EOF)
    {
        tot = 0;
        fill_n(head, n + 1, -1);
        while(m--)
        {
            int u,v; readi(u,v);
            addEdge(u,v); addEdge(v,u);
        }
        printf("%d\n", hungary(n)/2);
    }
    return 0;
}