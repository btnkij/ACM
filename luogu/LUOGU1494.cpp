/**
* Number:p1494
* Title:[国家集训队]小Z的袜子 /【模板】莫队
* Status:AC
* Tag:[莫队, 组合数学]
* desc: 多组询问，区间中任选两个数字，求它们相同的概率
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

const int MAXN = 50010;
int sz;      // 块大小
struct Query
{
    int L, R, id;
    bool operator<(const Query &rhs) const
    {
        int b1 = L / sz, b2 = rhs.L / sz;
        if (b1 != b2)
            return b1 < b2; // 不同块内按块号排序
        return (R < rhs.R) ^ (b1 & 1); // 偶数块内R升序，奇数块内R降序
    }
} querys[MAXN];
/*
a b c
(a*(a-1)/2*b*(b-1)/2*c*(c-1)/2)/((a+b+c)*(a+b+c-1)/2)
*/
// 莫队算法
ll sum1, sum2, cnt[MAXN]; // sum1-分子，sum2-总数，cnt[]-每种颜色的数量
ll ans1[MAXN], ans2[MAXN]; // ans1-答案的分子，ans2-答案的分母
void add(int color)
{
    ll &x = cnt[color];
    sum1 = sum1 - (x * (x - 1) / 2) + ((x + 1) * x / 2);
    sum2 = sum2 + 1;
    x++;
}
void erase(int color)
{
    ll &x = cnt[color];
    sum1 = sum1 - (x * (x - 1) / 2) + ((x - 1) * (x - 2) / 2);
    sum2 = sum2 - 1;
    x--;
}

ll gcd(ll a, ll b) // GCD模板
{
    return b == 0 ? a : gcd(b, a % b);
}

int c[MAXN]; // 序列
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m; // n-序列长度 m-询问数
    readi(n, m);
    rep(i, 1, n) readi(c[i]);
    sz = (int)sqrt(n + 1); // 最优分块复杂度为O(n^(3/2))
    rep(i, 1, m) // 离线所有询问
    {
        readi(querys[i].L, querys[i].R);
        querys[i].id = i;
    }
    sort(querys + 1, querys + m + 1);
    int wndL = 1, wndR = 0; // 当前的滑动窗口[wndL, wndR]，初始化为空集
    rep(i, 1, m)
    {
        Query &q = querys[i];
        while (wndR < q.R) // 先扩大窗口
            add(c[++wndR]);
        while (wndL > q.L)
            add(c[--wndL]);
        while (wndR > q.R) // 再缩小窗口
            erase(c[wndR--]);
        while (wndL < q.L)
            erase(c[wndL++]);
        if (sum1 == 0)
            ans1[q.id] = 0, ans2[q.id] = 1;
        else
        {
            ll sum3 = sum2 * (sum2 - 1) / 2;
            ll d = gcd(sum1, sum3);
            ans1[q.id] = sum1 / d, ans2[q.id] = sum3 / d;
        }
    }
    rep(i, 1, m) printf("%lld/%lld\n", ans1[i], ans2[i]);
    return 0;
}