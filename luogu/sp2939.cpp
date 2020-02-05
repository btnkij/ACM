/**
* Number:sp2939
* Title:QTREE5 - Query on a tree V
* Status:AC
* Tag:[动态点分治]
* desc: 多次询问树上一个点到最近白点的距离
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
struct Edge // 链式前向星模板
{
    int from, to, nxt;
} edges[MAXN * 2];
int head[MAXN], edgeid;
void addedge(int from, int to)
{
    edges[edgeid] = {from, to, head[from]};
    head[from] = edgeid++;
}

struct Heap // 小根堆，multiset很慢，请勿替代
{
    priority_queue<int, vector<int>, greater<int>> open, close;
    int size()
    {
        return open.size() - close.size();
    }
    void push(int val)
    {
        open.push(val);
    }
    void pop(int val)
    {
        close.push(val);
    }
    int top()
    {
        while (!close.empty() && open.top() == close.top())
            open.pop(), close.pop();
        return open.top();
    }
};

struct Node // 点分树的节点
{
    int color;           // 节点颜色 1-白色 0-黑色
    int fa, dep, up[20]; // fa-父节点 dep-深度 up[i]-到深度为i的重心的距离
    Heap dis;            // 分治子树中所有节点到分治重心的距离
} tree[MAXN];
int root, totrk, rk[MAXN], maxrk;
bool cg[MAXN];
void getcg(int u, int pre) // 点分治模板：计算树的重心，答案保存到root中
{
    rk[u] = 1;
    int tmp = -INF;
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre || cg[v])
            continue;
        getcg(v, u);
        tmp = max(tmp, rk[v]);
        rk[u] += rk[v];
    }
    tmp = max(tmp, totrk - rk[u]);
    if (tmp < maxrk)
        maxrk = tmp, root = u;
}
void dfs(int u, int pre, int dep) // 计算up[]
{
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (v == pre || cg[v])
            continue;
        tree[v].up[dep] = tree[u].up[dep] + 1;
        dfs(v, u, dep);
    }
}
// 建点分树：u-当前节点 pre-上一级分治重心 dep-深度 totrk-当前子树大小
void build(int u, int pre, int dep, int totrk)
{
    ::totrk = totrk, maxrk = INF;
    getcg(u, 0);
    cg[u = root] = true; // 注意root是全局变量，可能更改，所以先赋值给u
    Node &cur = tree[u];
    cur.fa = pre, cur.dep = dep, cur.color = 0;
    dfs(u, 0, dep);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        int v = edges[i].to;
        if (cg[v])
            continue;
        if (rk[v] > rk[u]) // root上方的子树rk计算不正确，需在这里修正
            rk[v] = totrk - rk[u];
        build(v, u, dep + 1, rk[v]);
    }
}
void change(int u) // 切换节点的颜色
{
    Node &nod = tree[u];
    nod.color ^= 1;
    if (nod.color == 1)                    // 如果变成白点，自底向上添加u到上级重心的距离
        for (int x = u; x; x = tree[x].fa) // 包括到自身的距离
            tree[x].dis.push(nod.up[tree[x].dep]);
    else // 如果变成白点，自底向上删除距离信息
        for (int x = u; x; x = tree[x].fa)
            tree[x].dis.pop(nod.up[tree[x].dep]);
}
int query(int u) // 查询离u最近的白点的距离
{
    int ans = INF;
    for (int x = u; x; x = tree[x].fa)
        if (tree[x].dis.size())
            ans = min(ans, tree[u].up[tree[x].dep] + tree[x].dis.top());
    return ans == INF ? -1 : ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);                  // 节点数
    clr(head, -1), edgeid = 0; // 链式前向星的初始化
    repne(i, 1, n)
    {
        int u, v;
        readi(u, v);
        addedge(u, v), addedge(v, u);
    }
    build(1, 0, 1, n); // 建点分树
    int q;
    readi(q); // 询问数
    while (q--)
    {
        int op, x;
        readi(op, x);
        if (op == 0) // 切换节点x的颜色
            change(x);
        else if (op == 1) // 查询与x最近的白点的距离
            printf("%d\n", query(x));
    }
    return 0;
}