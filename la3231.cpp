/**
* Number:la3231
* Title:Fair Share
* Status:AC
* Tag:[网络流, 最大流, 二分]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

const int MAXN=12000;
const int MAXM=80000;

struct Edge
{
    int from,to,flow,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int flow)
{
    edges[edgeid]=(Edge){from,to,flow,head[from]};
    head[from]=edgeid++;
}

int src,dst;
int dep[MAXN],cur[MAXN],num[MAXN],pre[MAXN];
void addflow(int from,int to,int flow)
{
    addedge(from,to,flow);
    addedge(to,from,0);
}
void bfs(int n)
{
    fill_n(dep,n+1,n); dep[dst]=0;
    queue<int> Q; Q.push(dst);
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e = edges[i ^ 1];
            if (dep[e.from] < n || e.flow <= 0)
                continue;
            dep[e.from] = dep[u] + 1;
            Q.push(e.from);
        }
    }
}
int agument()
{
    int f = INF;
    for(int u=dst;u!=src;u=edges[pre[u]].from)
    {
        f=min(f,edges[pre[u]].flow);
    }
    for(int u=dst;u!=src;u=edges[pre[u]].from)
    {
        edges[pre[u]].flow -= f;
        edges[pre[u] ^ 1].flow += f;
    }
    return f;
}
int isap(int n)
{
    fill_n(num,n+1,0);
    bfs(n);
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
            ans += agument();
            u = src;
            continue;
        }
        bool found = false;
        for (int &i = cur[u]; ~i; i = edges[i].nxt)
        {
            Edge& e = edges[i];
            if (dep[e.to] + 1 != dep[u] || e.flow <= 0)continue;
            found = true;
            u = e.to, pre[u] = i;
            break;
        }
        if (!found)
        {
            int mindep = n - 1;
            for (int i = head[u]; ~i; i = edges[i].nxt)
            {
                Edge& e = edges[i];
                if (e.flow > 0)
                    mindep = min(mindep, dep[e.to]);
            }
            if (--num[dep[u]] == 0)break;
            num[dep[u] = mindep + 1]++;
            cur[u] = head[u];
            if (u != src)u = edges[pre[u]].from;
        }
    }
    return ans;
}

int link[MAXN][2];
bool check(int n,int m,int mid)
{
    src=n+m+1, dst=n+m+2;
    clr(head,-1); edgeid=0;
    rep(i,1,n)addflow(src,i,mid);
    rep(i,1,m)
    {
        addflow(n+i,dst,1);
        addflow(link[i][0],n+i,1);
        addflow(link[i][1],n+i,1);
    }
    int maxflow=isap(n+m+2);
    return maxflow==m;
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
        int n,m; readi(n,m);
        rep(i,1,m)readi(link[i][0],link[i][1]);
        int lt=0,rt=m;
        while(lt<rt)
        {
            int mid=(lt+rt)>>1;
            if(check(n,m,mid))rt=mid;
            else lt=mid+1;
        }
        printf("%d\n",lt);
    }
    return 0;
}