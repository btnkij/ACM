/**
* Number:loj10085
* Title:「一本通 3.3 练习 2」虫洞 Wormholes
* Status:AC
* Tag:[spfa]
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
    int from,to;
    int dis;
}edges[6000];
int head[510], nxt[6000], tot;
void addEdge(int from, int to, int dis)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int dis[510];
bool vis[510];
bool spfa(int u)
{
    vis[u]=true;
    bool ans=false;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        int c=edges[i].dis;
        if(dis[u]+c<dis[v])
        {
            dis[v]=dis[u]+c;
            if(vis[v] || spfa(v))
            {
                ans=true;
                break;
            }
        }
    }
    vis[u]=false;
    return ans;
}

int n; // 节点数
bool check()
{
    std::fill(vis, vis+n+1, false);
    std::fill(dis, dis+n+1, 0);
    for(int i=1;i<=n;i++)if(spfa(i))return true;
    return false;
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
        int m,w;
        readi(n,m,w);
        fill(head,head+n+1,-1);
        tot=0;
        while(m--)
        {
            int u,v,w; readi(u,v,w);
            addEdge(u,v,w); addEdge(v,u,w);
        }
        while(w--)
        {
            int u,v,w; readi(u,v,w);
            addEdge(u,v,-w);
        }
        if(check())printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}