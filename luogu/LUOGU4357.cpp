/**
* Number:p4357
* Title: [CQOI2016]K远点对
* Status:AC
* Tag:[k-d tree, 启发式搜索]
* desc: 求平面第k远的点对的欧式距离的平方
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

const int MAX_DIM = 2; // 问题空间为二维平面
int dim;               // 当前划分的维度

struct Point
{
    int x[MAX_DIM];
    bool operator<(const Point &rhs) const
    {
        return x[dim] < rhs.x[dim];
    }
} pos[100010];
ll dis(const Point &lhs, const Point &rhs) // 欧式距离
{
    ll ans = 0;
    for (int i = 0; i < MAX_DIM; i++)
        ans += (ll)(lhs.x[i] - rhs.x[i]) * (lhs.x[i] - rhs.x[i]);
    return ans;
}

struct Node
{
    Point p, ul, br; // p-当前点 ul(br)-划分空间的最小（最大）坐标
    Node *son[2];    // 左右儿子
    void pushup()
    {
        ul = br = p;
        for (int d = 0; d < 2; d++)
        {
            if (son[d])
            {
                for (int i = 0; i < MAX_DIM; i++)
                {
                    ul.x[i] = min(ul.x[i], son[d]->ul.x[i]);
                    br.x[i] = max(br.x[i], son[d]->br.x[i]);
                }
            }
        }
    }
} tree[100010], *root, *tail;
void init()
{
    root = tail = tree;
}
void build(Node *&u, Point *beg, Point *end, int dep)
{
    if (beg >= end)
        return;
    dim = dep % MAX_DIM;
    Point *mid = beg + (end - beg) / 2;
    nth_element(beg, mid, end);
    u = tail++;
    u->p = *mid;
    build(u->son[0], beg, mid, dep + 1);
    build(u->son[1], mid + 1, end, dep + 1);
    u->pushup();
}

priority_queue<ll, vector<ll>, greater<ll>> topk;
ll h(const Point &p, const Node *u) // 估计函数：点到u的空间的最大距离
{
    return max(
        max(dis(p, u->ul), dis(p, (Point){u->ul.x[0], u->br.x[1]})),
        max(dis(p, u->br), dis(p, (Point){u->br.x[0], u->ul.x[1]})));
}
void dfs(const Node *u, const Point &p)
{
    ll hm = dis(p, u->p);
    if (hm > topk.top())
    {
        topk.pop();
        topk.push(hm);
    }
    for (int i = 0; i < 2; i++)
    {
        if (u->son[i] && h(p, u->son[i]) > topk.top())
        {
            dfs(u->son[i], p);
        }
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, k; // n个点，求第k远
    readi(n, k);
    repne(i, 0, n) readi(pos[i].x[0], pos[i].x[1]);
    init();
    build(root, pos, pos + n, 0);
    repne(i, 0, k << 1) topk.push(0); // 由于对称性，一个点对会被统计两次
    repne(i, 0, n)
        dfs(root, pos[i]);
    printf("%lld\n", topk.top());
    return 0;
}