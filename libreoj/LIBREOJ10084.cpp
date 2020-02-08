/**
* Number:loj10084
* Title:「一本通 3.3 练习 1」最小圈
* Status:AC
* Tag:[spfa, 负环]
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
    double dis;
}edges[20010];
int head[3010], nxt[20010], tot;
void addEdge(int from, int to, double dis)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to, e.dis=dis;
    nxt[tot]=head[from];
    head[from]=tot++;
}

double mid;
double dis[3010];
bool vis[3010];
bool spfa(int u)
{
    vis[u]=true;
    bool ans=false;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        double c=edges[i].dis;
        if(dis[u]+c-mid<dis[v])
        {
            dis[v]=dis[u]+c-mid;
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

int n,m;
bool check()
{
    fill(vis, vis+n+1, false);
    fill(dis, dis+n+1, 0);
    rep(i,1,n)if(spfa(i))return true;
    return false;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    fill(head,head+n+1,-1);
    double lt=1e100, rt=-1e100;
    while(m--)
    {
        int u,v; readi(u,v);
        double w; scanf("%lf",&w);
        addEdge(u,v,w);
        lt=min(lt,w), rt=max(rt,w);
    }
    while(rt-lt>1e-10)
    {
        mid=(lt+rt)/2;
        if(check())rt=mid;
        else lt=mid;
    }
    printf("%.8lf",lt);
    return 0;
}