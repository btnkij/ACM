/**
* Number:p3806
* Title:【模板】点分治1
* Status:AC
* Tag:[点分治]
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
    int from, to, dis;
}edges[20010];
int head[10010], nxt[20010], tot;
void addEdge(int from, int to, int dis)
{
    Edge& e = edges[tot];
    e.from = from, e.to = to, e.dis = dis;
    nxt[tot] = head[from];
    head[from] = tot++;
}

int root, sum;
int rk[10010], maxrk;
bool cg[10010];
void getcg(int u, int pre)
{
    rk[u] = 1;
    int tmp = -INF;
    for(int i = head[u]; ~i; i = nxt[i])
    {
        int v = edges[i].to;
        if(v == pre || cg[v])continue;
        getcg(v, u);
        tmp = max(tmp, rk[v]);
        rk[u] += rk[v];
    }
    tmp = max(tmp, sum - rk[u]);
    if(tmp < maxrk)maxrk = tmp, root = u;
}

int dis[10010],len,len1;
void getdis(int u, int pre, int d)
{
    dis[len+len1]=d;
    len1++;
    for(int i=head[u];~i;i=nxt[i])
    {
        Edge& e=edges[i];
        if(cg[e.to] || e.to==pre)continue;
        getdis(e.to,u,d+e.dis);
    }
}

int n,m;
bool exist[10000010];
int query[110];
bool ok[110];
void solve(int u)
{
    exist[0]=true;
    cg[u]=true;
    len=0;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(cg[v])continue;
        len1=0;
        getdis(v,u,edges[i].dis);
        repne2(j,0,len1,k,0,m)
        {
            int d=dis[j+len];
            if(query[k]>=d && exist[query[k]-d])
            {
                ok[k]=true;
            }
        }
        repne(j,0,len1)exist[dis[j+len]]=true;
        len+=len1;
    }
    repne(i,0,len)exist[dis[i]]=false;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(cg[v])continue;
        maxrk=INF, sum=rk[v];
        getcg(v,0);
        solve(root);
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    mset(head,-1);
    repne(i,1,n)
    {
        int u,v,w; readi(u,v,w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    repne(i,0,m)readi(query[i]);
    maxrk=INF, sum=n;
    getcg(1,0);
    solve(root);
    repne(i,0,m)
    {
        puts(ok[i]?"AYE":"NAY");
    }
    return 0;
}