/**
* Number:hdu6598
* Title:Harmonious Army
* Status:AC
* Tag:[网络流]
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
    ll cap;
    int nxt;
}edges[40010];
int head[510],edge_id;
void addedge(int from,int to,ll cap)
{
    edges[edge_id]=(Edge){from,to,cap,head[from]};
    head[from]=edge_id++;
}

int n,m,src,dst;
int dep[510];
bool bfs()
{
    mset(dep,0);
    queue<int> Q;
    Q.push(src);
    dep[src]=1;
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(dep[e.to] || e.cap<=0)continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]>0;
}
int cur[510];
ll dfs(int u,ll flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(dep[u]+1!=dep[e.to] || e.cap<=0)continue;
        ll f=dfs(e.to, min(flow, e.cap));
        if(f)
        {
            e.cap-=f;
            edges[i^1].cap+=f;
            return f;
        }
    }
    return 0;
}
ll dinic()
{
    ll ans=0;
    while(bfs())
    {
        memcpy(cur,head,sizeof(head));
        int f;
        while(f=dfs(src,INF))
        {
            ans+=f;
        }
    }
    return ans;
}

ll w1[510],w2[510];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n,m)!=EOF)
    {
        mset(head,-1);
        edge_id=0;
        mset(w1,0); mset(w2,0);
        src=n+1, dst=n+2;
        ll ans=0;
        repne(i,0,m)
        {
            int u,v; readi(u,v);
            ll a,b,c; scanf("%lld %lld %lld",&a,&b,&c);
            ans+=a+b+c;
            w1[u]+=a+b, w1[v]+=a+b;
            w2[u]+=b+c, w2[v]+=b+c;
            ll d=a+c-(b<<1);
            addedge(u,v,d); addedge(v,u,d);
        }
        ans<<=1;
        rep(i,1,n)
        {
            addedge(src,i,w1[i]); addedge(i,src,0);
            addedge(i,dst,w2[i]); addedge(dst,i,0);
        }
        ans=(ans-dinic())>>1;
        printf("%lld\n",ans);
    }
    return 0;
}