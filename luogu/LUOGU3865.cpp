/**
* Number:p3865
* Title:ST表
* Status:AC
* Tag:[rmq]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef int ll;

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct sparse_table
{
    static const int MAXN = 1e5 + 10;
    static const int LOGN = 17;
    int mm[MAXN];
    int dp[MAXN][LOGN];
    void init(int n)
    {
        for (int i = 2; i <= n; i++)
            mm[i] = i & (i - 1) ? mm[i - 1] : mm[i - 1] + 1;
        for (int k = 1; k < LOGN; k++)
        {
            int L = 1 << k;
            for (int i = 1; i + L - 1 <= n; i++)
                dp[i][k] = max(dp[i][k - 1], dp[i + (L >> 1)][k - 1]);
        }
    }
    ll rmq(int lt, int rt)
    {
        int k = mm[rt - lt];
        return max(dp[lt][k], dp[rt - (1 << k) + 1][k]);
    }
} solver;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, q;
    readi2(n, q);
    rep(i, 1, n) readi(solver.dp[i][0]);
    solver.init(n);
    while (q--)
    {
        int lt, rt;
        readi2(lt, rt);
        printf("%d\n", solver.rmq(lt, rt));
    }
    return 0;
}