/**
* Number:sp2939
* Title:QTREE5 - Query on a tree V
* Status:?
* Tag:[]
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

const int MAXN = 1e5 + 10;
struct Edge // 链式前向星模板
{
    int from, to, dis, nxt;
} edges[MAXN * 2];
int head[MAXN], edgeid;
void addedge(int from, int to, int dis)
{
    edges[edgeid] = {from, to, dis, head[from]};
    head[from] = edgeid++;
}

struct Heap // 大根堆，multiset很慢，请勿替代
{
    priority_queue<int> open, close;
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
    int top2()
    {
        int k1 = top();
        open.pop();
        int k2 = top();
        open.push(k1);
        return k1 + k2;
    }
};

int root, tot, rk[MAXN], maxrk;
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
    tmp = max(tmp, tot - rk[u]);
    if (tmp < maxrk)
        root = u, maxrk = tmp;
}

struct Node // 点分树的节点
{
    int color;           // 节点颜色 1-白色 0-黑色
    int fa, dep, up[20]; // fa-父节点 dep-深度 up[i]-到深度为i的重心的距离
    int ans;             // 子树的答案
    Heap dis, maxdis;    // dis-到当前节点的父节点的距离 maxdis-子树dis的最大值
} tree[MAXN];
Heap ans;          // 维护所有节点ans的堆
void pushup(int u) // 计算当前节点的ans，并将dis推到父节点
{
    tree[u].ans = (tree[u].color == 1 ? 0 : -INF);   // 如果是白点，答案初始为到自身的距离0
    if (tree[u].maxdis.size() && tree[u].color == 1) // 子节点到当前节点的距离
        tree[u].ans = max(tree[u].ans, tree[u].maxdis.top());
    if (tree[u].maxdis.size() >= 2) // 经过分治重心的最长链
        tree[u].ans = max(tree[u].ans, tree[u].maxdis.top2());
    ans.push(tree[u].ans);
    if (tree[u].dis.size() && tree[u].fa)
        tree[tree[u].fa].maxdis.push(tree[u].dis.top());
}
void dfs(int u, int pre, int dep) // 计算当前节点的dis
{
    if (dep > 1)
        tree[root].dis.push(tree[u].up[dep - 1]);
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (e.to == pre || cg[e.to])
            continue;
        tree[e.to].up[dep] = tree[u].up[dep] + e.dis;
        dfs(e.to, u, dep);
    }
}
// 建点分树：u-当前节点 pre-上一级分治重心 dep-深度 totrk-当前子树大小
void build(int u, int pre, int dep, int totrk)
{
    tot = totrk, maxrk = INF;
    getcg(u, 0);
    cg[u = root] = true; // 注意root是全局变量，可能更改，所以先赋值给u
    Node &cur = tree[u];
    cur.fa = pre, cur.dep = dep, cur.color = 1; // 初始所有点都是白点
    dfs(u, 0, dep);                             // 计算cur.dis
    for (int i = head[u]; ~i; i = edges[i].nxt)
    {
        Edge &e = edges[i];
        if (cg[e.to])
            continue;
        if (rk[e.to] > rk[u]) // root上方的子树rk计算不正确，需在这里修正
            rk[e.to] = totrk - rk[u];
        build(e.to, u, dep + 1, rk[e.to]);
    }
    pushup(u);
}
void change(int u) // 切换节点的颜色
{
    static int trace[MAXN];
    for (int i = tree[u].dep, x = u; i; i--, x = tree[x].fa)
        trace[i] = x;
    for (int i = 1; i <= tree[u].dep; i++) // 自上而下删除与u有关的信息
    {
        Node &cur = tree[trace[i]];
        if (cur.fa && cur.dis.size())
            tree[cur.fa].maxdis.pop(cur.dis.top());
        if (cur.dep > 1 && tree[u].color == 1)
            cur.dis.pop(tree[u].up[cur.dep - 1]);
        ans.pop(cur.ans);
    }
    tree[u].color ^= 1;                    // 切换颜色
    for (int i = tree[u].dep; i >= 1; i--) // 自底向上重新计算与u有关的信息
    {
        int x = trace[i];
        if (tree[x].dep > 1 && tree[u].color == 1)
            tree[x].dis.push(tree[u].up[i - 1]);
        pushup(x);
    }
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
        addedge(u, v, 1), addedge(v, u, 1);
    }
    build(1, 0, 1, n); // 建点分树
    int q;
    readi(q); // 询问数
    while (q--)
    {
        char op[4];
        reads(op);
        if (op[0] == 'C') // 切换节点x的颜色
        {
            int x;
            readi(x);
            change(x);
        }
        else if (op[0] == 'A') // 查询距离最远的两个白点
        {
            if (ans.top() == -INF) // 不存在白点
                puts("-1");
            else
                printf("%d\n", ans.top());
        }
    }
    return 0;
}