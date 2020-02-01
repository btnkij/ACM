/**
* Number:p1903
* Title:[国家集训队]数颜色 / 维护队列 /【模板】带修莫队
* Status:AC
* Tag:[带修改莫队]
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

inline int readu()
{
    register int num = 0;
    register char ch;
    do
    {
        ch = getchar();
    } while (ch < '0' || ch > '9');
    do
    {
        num = (num << 3) + (num << 1) + (ch & 0xF);
        ch = getchar();
    } while ('0' <= ch && ch <= '9');
    return num;
}

const int MAXN = 140000;
int sz;
struct Query
{
    int L, R, T, id;
    bool operator<(const Query &rhs) const
    {
        if (L / sz != rhs.L / sz)
            return L < rhs.L;
        if (R / sz != rhs.R / sz)
            return R < rhs.R;
        return T < rhs.T;
    }
} querys[MAXN];
struct Update
{
    int pos, val;
} updates[MAXN];

int s[MAXN], ans[MAXN];
int cnt[1000010], wnd;
int wndL = 1, wndR = 0, wndT = 0;
void add(int color)
{
    if (++cnt[color] == 1)
        wnd++;
}
void erase(int color)
{
    if (--cnt[color] == 0)
        wnd--;
}
void change(Update &upd)
{
    if (wndL <= upd.pos && upd.pos <= wndR)
    {
        erase(s[upd.pos]);
        add(upd.val);
    }
    swap(upd.val, s[upd.pos]);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n = readu(), m = readu();
    rep(i, 1, n) s[i] = readu();
    sz = (int)pow(n + 1, 2.0 / 3.0);
    int len1 = 0, len2 = 0;
    int t = 0;
    while (m--)
    {
        char op[4];
        scanf("%s", op);
        int x = readu(), y = readu();
        if (op[0] == 'Q')
            querys[len1] = {x, y, t, len1}, len1++;
        else if (op[0] == 'R')
            updates[len2++] = {x, y}, t++;
    }
    sort(querys, querys + len1);
    repne(i, 0, len1)
    {
        Query &q = querys[i];
        while (wndT < q.T)
            change(updates[wndT++]);
        while (wndT > q.T)
            change(updates[--wndT]);
        while (wndR < q.R)
            add(s[++wndR]);
        while (wndL > q.L)
            add(s[--wndL]);
        while (wndR > q.R)
            erase(s[wndR--]);
        while (wndL < q.L)
            erase(s[wndL++]);
        ans[q.id] = wnd;
    }
    repne(i, 0, len1) printf("%d\n", ans[i]);
    return 0;
}