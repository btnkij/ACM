/**
* Number:hdu5977
* Title:Garden of Eden
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
    int from, to;
}edges[50010*2];
int head[50010],nxt[50010*2],tot;
int type[50010];
void addEdge(int from,int to)
{
    Edge& e=edges[tot];
    e.from=from, e.to=to;
    nxt[tot]=head[from];
    head[from]=tot++;
}

int root, sum;
int rk[50010], maxrk;
bool cg[50010];
void getcg(int u, int pre)
{
    rk[u]=1;
    int tmp=-INF;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre || cg[v])continue;
        getcg(v,u);
        tmp=max(tmp,rk[v]);
        rk[u]+=rk[v];
    }
    tmp=max(tmp,sum-rk[u]);
    if(tmp<maxrk)maxrk=tmp, root=u;
}

int state[50010],len;
int cnt[1<<12];
int n,k,all;
void dfs(int u, int pre, int s)
{
    s|=type[u];
    cnt[s]++;
    state[len++]=s;
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(v==pre || cg[v])continue;
        dfs(v,u,s);
    }
}

ll calc(int u, int s)
{
    memset(cnt,0,sizeof(int)*(all+2));
    len=0;
    dfs(u,0,s);
    for(int i=0;i<k;i++)
    {
        for(int j=all;j>=0;j--)
        {
            if(!((1<<i)&j))
                cnt[j]+=cnt[(1<<i)|j];
        }
    }
    ll res=0;
    for(int i=0;i<len;i++)
        res+=cnt[state[i]^all];
    return res;
}

ll solve(int u)
{
    maxrk=INF, sum=rk[u];
    getcg(u,0);
    u=root;
    cg[u]=true;
    ll res=calc(u,0);
    for(int i=head[u];~i;i=nxt[i])
    {
        int v=edges[i].to;
        if(cg[v])continue;
        res-=calc(v,type[u]);
        res+=solve(v);
    }
    return res;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n,k)!=EOF)
    {
        tot=0;
        mset(head,-1);
        mset(cg,false);
        all=(1<<k)-1;
        rep(i,1,n)
        {
            int t; readi(t);
            type[i]=1<<(t-1);
        }
        repne(i,1,n)
        {
            int u,v; readi(u,v);
            addEdge(u,v);
            addEdge(v,u);
        }
        rk[1]=n;
        ll ans=solve(1);
        printf("%lld\n",ans);
    }
    return 0;
}