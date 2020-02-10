/**
* Number:luogu2762
* Title:太空飞行计划问题
* Status:AC
* Tag:[网络流, 最小割, 最大权闭合子图]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=200;
const int MAXM=2000;
struct Edge
{
    int from,to,flow,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int flow)
{
    edges[edgeid]={from,to,flow,head[from]};
    head[from]=edgeid++;
}
void addflow(int from,int to,int flow)
{
    addedge(from,to,flow);
    addedge(to,from,0);
}

int dep[MAXN], cur[MAXN], num[MAXN], pre[MAXN];
void bfs(int n, int dst)
{
    fill_n(dep, n + 1, n);
    dep[dst] = 0;
    queue<int> Q;
    Q.push(dst);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i ^ 1];
            if (dep[e.from] < n || e.flow <= 0) continue;
            dep[e.from] = dep[u] + 1;
            Q.push(e.from);
        }
    }
}
int augment(int src, int dst)
{
    int f = INF;
    for (int u = dst; u != src; u = edges[pre[u]].from)
        f = min(f, edges[pre[u]].flow);
    for (int u = dst; u != src; u = edges[pre[u]].from)
    {
        edges[pre[u]].flow -= f;
        edges[pre[u] ^ 1].flow += f;
    }
    return f;
}
int isap(int n, int src, int dst)
{
    fill_n(num, n + 1, 0);
    bfs(n, dst);
    for (int i = 1; i <= n; i++)
    {
        num[dep[i]]++;
        cur[i] = head[i];
    }
    int u = src;
    int ans = 0;
    while (dep[src] < n)
    {
        if (u == dst)
        {
            ans += augment(src, dst);
            u = src;
            continue;
        }
        bool found = false;
        for (int &i = cur[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (dep[e.to] + 1 != dep[u] || e.flow <= 0) continue;
            found = true;
            u = e.to;
            pre[u] = i;
            break;
        }
        if (!found)
        {
            int mindep = n - 1;
            for (int i = head[u]; ~i; i = edges[i].nxt)
            {
                Edge &e = edges[i];
                if (e.flow > 0) mindep = min(mindep, dep[e.to]);
            }
            if (--num[dep[u]] == 0) break;
            num[dep[u] = mindep + 1]++;
            cur[u] = head[u];
            if (u != src) u = edges[pre[u]].from;
        }
    }
    return ans; // 返回最大流的值
}

bool vis[MAXN];
void dfs(int u)
{
    vis[u]=true;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        // if(i&1)continue;
        Edge& e=edges[i];
        if(e.flow==0 || vis[e.to])continue;
        dfs(e.to);
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m,n; cin>>m>>n;
    int src=m+n+1, dst=src+1;
    fill_n(head,dst+5,-1), edgeid=0;
    int sum=0;
    cin.get();
    rep(i,1,m)
    {
        string line; getline(cin,line);
        stringstream ss(line);
        int t; ss>>t;
        sum+=t;
        addflow(src,i,t);
        while(ss>>t)addflow(i,m+t,INF);
    }
    rep(i,1,n)
    {
        int t; cin>>t;
        addflow(m+i,dst,t);
    }
    int ans=sum-isap(dst,src,dst);
    dfs(src);
    rep(i,1,m)if(vis[i])cout<<i<<' ';
    cout<<'\n';
    rep(i,1,n)if(vis[m+i])cout<<i<<' ';
    cout<<'\n'<<ans;
    return 0;
}