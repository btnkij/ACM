/**
* Number:p4114
* Title:Qtree1
* Status:AC
* Tag:[树链剖分, 线段树]
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

const int MAXN = 1e4 + 10;
struct Edge
{
    int from, to, dis, nxt;
} edges[MAXN << 1];
int head[MAXN], edgeid;
void addedge(int from, int to, int dis)
{
    edges[edgeid] = {from, to, dis, head[from]};
    head[from] = edgeid++;
}

struct QTreeNode
{
    int val, dep, sz, pos, fa, son, top;
} nodes[MAXN];
int dfsid = 0, rpos[MAXN];
void dfs1(int u, int pre)
{
    QTreeNode &cur = nodes[u];
    cur.fa = pre;
    cur.dep = nodes[pre].dep + 1;
    cur.sz = 1;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (e.to == pre)
        {
            cur.val = e.dis;
            continue;
        }
        dfs1(e.to, u);
        cur.sz += nodes[e.to].sz;
        if (nodes[e.to].sz > nodes[cur.son].sz)
            cur.son = e.to;
    }
}
void dfs2(int u, int top)
{
    QTreeNode &cur = nodes[u];
    cur.pos = ++dfsid, rpos[dfsid] = u;
    cur.top = top;
    if (cur.son)
        dfs2(cur.son, top);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (e.to == cur.fa || e.to == cur.son)
            continue;
        dfs2(e.to, e.to);
    }
}

int maxv[MAXN << 2];
void pushup(int p)
{
    maxv[p] = max(maxv[p << 1], maxv[p << 1 | 1]);
}
void build(int p, int lt, int rt)
{
    if (lt == rt)
    {
        maxv[p] = nodes[rpos[lt]].val;
        return;
    }
    int mid = (lt + rt) >> 1;
    build(p << 1, lt, mid), build(p << 1 | 1, mid + 1, rt);
    pushup(p);
}
void update(int p, int lt, int rt, int qpos, int qval)
{
    if (lt == rt)
    {
        maxv[p] = qval;
        return;
    }
    int mid = (lt + rt) >> 1;
    if (qpos <= mid)
        update(p << 1, lt, mid, qpos, qval);
    else
        update(p << 1 | 1, mid + 1, rt, qpos, qval);
    pushup(p);
}
int query(int p, int lt, int rt, int qlt, int qrt)
{
    if (qlt <= lt && rt <= qrt)
        return maxv[p];
    int mid = (lt + rt) >> 1;
    int ans = 0;
    if (qlt <= mid)
        ans = max(ans, query(p << 1, lt, mid, qlt, qrt));
    if (mid < qrt)
        ans = max(ans, query(p << 1 | 1, mid + 1, rt, qlt, qrt));
    return ans;
}

int query_chain(int n, int x, int y)
{
    int ans = 0;
    int topx = nodes[x].top, topy = nodes[y].top;
    while (topx != topy)
    {
        if (nodes[topx].dep > nodes[topy].dep)
            swap(topx, topy), swap(x, y);
        ans = max(ans, query(1, 1, n, nodes[topy].pos, nodes[y].pos));
        y = nodes[topy].fa, topy = nodes[y].top;
    }
    if (x == y)
        return ans;
    if (nodes[x].dep > nodes[y].dep)
        swap(x, y);
    ans = max(ans, query(1, 1, n, nodes[nodes[x].son].pos, nodes[y].pos));
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    clr(head, -1), edgeid = 0;
    repne(i, 1, n)
    {
        int u, v, w;
        readi(u, v, w);
        addedge(u, v, w), addedge(v, u, w);
    }
    dfs1(1, 0), dfs2(1, 1);
    build(1, 1, n);
    char op[8];
    while (reads(op) != EOF && op[0] != 'D')
    {
        int x, y;
        readi(x, y);
        if (op[0] == 'Q')
            printf("%d\n", query_chain(n, x, y));
        else if (op[0] == 'C')
        {
            Edge &e = edges[(x - 1) << 1];
            x = nodes[e.from].dep > nodes[e.to].dep ? e.from : e.to;
            update(1, 1, n, nodes[x].pos, y);
        }
    }
    return 0;
}