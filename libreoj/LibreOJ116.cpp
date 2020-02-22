/**
* Number:loj116
* Title:有源汇有上下界最大流
* Status:AC
* Tag:[网络流, 有源汇有上下界最大流]
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

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 400;
const int MAXM = 10010;
struct Edge
{
    int from, to, flow, nxt;
} edges[MAXM * 6]; // 注意开6倍
int head[MAXN], edgeid;
void addedge(int from, int to, int flow)
{
    edges[edgeid] = {from, to, flow, head[from]};
    head[from] = edgeid++;
}

int isrc, idst; // isrc-虚拟源点 idst-虚拟汇点
void addflow(int from, int to, int flow)
{
    if (flow == 0)
        return;
    addedge(from, to, flow);
    addedge(to, from, 0);
}
void addflow(int from, int to, int lower, int upper)
{
    addflow(from, to, upper - lower); // from到to连分离出来的流量
    addflow(isrc, to, lower);         // 虚拟源点将下界流量送到to
    addflow(from, idst, lower);       // from将下界流量送到虚拟汇点
}

int dep[MAXN], cur[MAXN];
bool bfs(int n, int src, int dst)
{
    fill_n(dep, n + 1, 0);
    dep[src] = 1;
    queue<int> Q;
    Q.push(src);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (e.to == 0)
                continue;
            if (dep[e.to] || e.flow <= 0)
                continue;
            dep[e.to] = dep[u] + 1;
            Q.push(e.to);
        }
    }
    return dep[dst] > 0;
}
int dfs(int u, int dst, int flow)
{
    if (u == dst)
        return flow;
    for (int &i = cur[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (e.to == 0)
            continue;
        if (dep[e.to] != dep[u] + 1 || e.flow <= 0)
            continue;
        int f = dfs(e.to, dst, min(flow, e.flow));
        if (f)
        {
            e.flow -= f, edges[i ^ 1].flow += f;
            return f;
        }
    }
    return 0;
}
int dinic(int n, int src, int dst)
{
    int ans = 0, f;
    while (bfs(n, src, dst))
    {
        copy(head, head + n + 1, cur);
        while (f = dfs(src, dst, INF))
            ans += f;
    }
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, src, dst;
    readi(n, m, src, dst);
    isrc = n + 1, idst = isrc + 1; // 定义虚拟源汇点
    clr(head, -1);                 // 链式前向星的初始化
    int sum = 0;
    repne(i, 0, m)
    {
        int u, v, lower, upper;
        readi(u, v, lower, upper);
        addflow(u, v, lower, upper);
        sum += lower; // 统计下界流量
    }
    int id = edgeid;
    addflow(dst, src, INF);              // 汇点向源点连容量为INF的边，并记录这条边的ID
    if (dinic(n + 2, isrc, idst) == sum) // 如果虚拟源汇的流量能流满，则有可行解
    {
        int ans = edges[id ^ 1].flow; // 先加上可行流
        for (int i = head[isrc]; ~i; i = edges[i].nxt)
            edges[i ^ 1].to = 0;
        for (int i = head[idst]; ~i; i = edges[i].nxt)
            edges[i ^ 1].to = 0;
        edges[id].to = edges[id ^ 1].to = 0; // 删除点isrc、点idst和边id
        ans += dinic(n + 2, src, dst);       // 再加残量网络上的源点到汇点的最大流
        printf("%d", ans);
    }
    else
        puts("please go home to sleep"); // 无解
    return 0;
}