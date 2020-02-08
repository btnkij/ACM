/**
* Number:loj10086
* Title:「一本通 3.3 练习 3」Easy SSSP
* Status:AC spfa入队次数?
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

#define INF 0x3f3f3f3f3f3f3f3f
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
    ll dis;
}edges[200010];
int head[1010], nxt[200010], tot;
void addEdge(int from, int to, ll dis)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}

ll dis[1010];
bool vis[1010];
int cnt[1010];
int fa[1010];
bool spfa(int n, int src)
{
    queue<int> Q;
    Q.push(src);
    dis[src]=0;
    int lim=(int)sqrt(n);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        vis[u]=false;
        fa[u]=src;
        for(int i=head[u];~i;i=nxt[i])
        {
            int v=edges[i].to, c=edges[i].dis;
            if(dis[u]+c<dis[v])
            {
                cnt[v]++;
                if(cnt[v]>lim)return false;
                dis[v]=dis[u]+c;
                if(vis[v])continue;
                vis[v]=true;
                Q.push(v);
            }
        }
    }
    return true;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,s; readi(n,m,s);
    fill_n(head, n+1, -1);
    fill_n(dis, n+1, INF);
    while(m--)
    {
        int u,v,w; readi(u,v,w);
        addEdge(u,v,w);
    }
    bool flag=spfa(n,s);
    for(int i=1;i<=n && flag;i++)
    {
        if(!fa[i])flag=spfa(n,i);
    }
    if(flag)
    {
        rep(i,1,n)
        {
            if(fa[i]==s)printf("%lld\n",dis[i]);
            else printf("NoPath\n");
        }
    }
    else printf("-1");
    return 0;
}