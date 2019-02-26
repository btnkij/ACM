/**
 * 
 * ST表 区间最值查询
 * 
**/

#include <algorithm>

typedef int ll;

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
                dp[i][k] = std::max(dp[i][k - 1], dp[i + (L >> 1)][k - 1]);
        }
    }
    ll rmq(int lt, int rt)
    {
        int k = mm[rt - lt];
        return std::max(dp[lt][k], dp[rt - (1 << k) + 1][k]);
    }
};