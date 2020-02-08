/**
* Number:p4779
* Title:【模板】单源最短路径（标准版）
* Status:AC
* Tag:[dijkstra]
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

const int MAXN = 1e5 + 10;
const int MAXM = 2e5 + 10;
struct Edge
{
    int from, to;
    ll dis;
    int nxt;
} edges[MAXM];
int head[MAXN], edgeid;
void addedge(int from, int to, ll dis)
{
    edges[edgeid] = {from, to, dis, head[from]};
    head[from] = edgeid++;
}

struct HeapNode
{
    int pos;
    ll cost;
    bool operator<(const HeapNode &rhs) const
    {
        return cost > rhs.cost;
    }
};
ll dis[MAXN];
void dijkstra(int src)
{
    priority_queue<HeapNode> Q;
    Q.push({src, 0});
    clr(dis, INF), dis[src] = 0;
    while (!Q.empty())
    {
        HeapNode cur = Q.top();
        Q.pop();
        if (cur.cost != dis[cur.pos])
            continue;
        for (int i = head[cur.pos]; ~i; i = edges[i].nxt)
        {
            Edge &e = edges[i];
            if (cur.cost + e.dis < dis[e.to])
            {
                dis[e.to] = cur.cost + e.dis;
                Q.push({e.to, dis[e.to]});
            }
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, s;
    readi(n, m, s);
    edgeid = 0, fill_n(head, n + 1, -1);
    rep(i, 1, m)
    {
        int u, v, w;
        readi(u, v, w);
        addedge(u, v, w);
    }
    dijkstra(s);
    rep(i, 1, n) printf("%lld ", dis[i]);
    return 0;
}