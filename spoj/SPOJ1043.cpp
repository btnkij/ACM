/**
* Number:spoj1043
* Title:GSS1 - Can you answer these queries I
* Status:AC
* Tag:[线段树]
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

const int MAXN = 5e4 + 10;
struct Node
{
    int sum, lmax, rmax, amax;
    Node()
    {
        sum = 0;
        lmax = rmax = amax = -INF;
    }
    Node operator+(const Node &rhs) const
    {
        Node ans;
        ans.sum = sum + rhs.sum;
        ans.lmax = max(lmax, sum + rhs.lmax);
        ans.rmax = max(rhs.rmax, rhs.sum + rmax);
        ans.amax = max(max(amax, rhs.amax), rmax + rhs.lmax);
        return ans;
    }
} tree[MAXN * 4];
void pushup(int p)
{
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
}
void build(int p, int lt, int rt)
{
    Node &nod = tree[p];
    if (lt == rt)
    {
        readi(nod.sum);
        nod.lmax = nod.rmax = nod.amax = nod.sum;
        return;
    }
    int mid = (lt + rt) >> 1;
    build(p << 1, lt, mid);
    build(p << 1 | 1, mid + 1, rt);
    pushup(p);
}
Node query(int p, int lt, int rt, int qlt, int qrt)
{
    if (qlt <= lt && rt <= qrt)
        return tree[p];
    Node ans;
    int mid = (lt + rt) >> 1;
    if (qlt <= mid)
        ans = query(p << 1, lt, mid, qlt, qrt);
    if (mid < qrt)
        ans = ans + query(p << 1 | 1, mid + 1, rt, qlt, qrt);
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
    build(1, 1, n);
    int q;
    readi(q);
    while (q--)
    {
        int x, y;
        readi(x, y);
        printf("%d\n", query(1, 1, n, x, y).amax);
    }
    return 0;
}