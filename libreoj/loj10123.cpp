/**
* Number:ybt1545, loj10123
* Title:「一本通 4.2 练习 2」Balanced Lineup 
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct sparse_table
{
    static const int MAXN = 5e5 + 10;
    static const int LOGN = 17;
    int mm[MAXN];
    int dpmax[MAXN][LOGN], dpmin[MAXN][LOGN];
    void init(int n)
    {
        for (int i = 2; i <= n; i++)
            mm[i] = i & (i - 1) ? mm[i - 1] : mm[i - 1] + 1;
        for (int k = 1; k < LOGN; k++)
        {
            int L = 1 << k;
            for (int i = 1; i + L - 1 <= n; i++)
            {
                dpmax[i][k] = std::max(dpmax[i][k - 1], dpmax[i + (L >> 1)][k - 1]);
                dpmin[i][k] = std::min(dpmin[i][k - 1], dpmin[i + (L >> 1)][k - 1]);
            }
        }
    }
    ll query(int lt, int rt)
    {
        int k = mm[rt - lt];
        return std::max(dpmax[lt][k], dpmax[rt - (1 << k) + 1][k])
            - std::min(dpmin[lt][k], dpmin[rt - (1 << k) + 1][k]);
    }
}st;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m; readi(n, m);
    rep(i,1,n)
    {
        readi(st.dpmax[i][0]);
        st.dpmin[i][0]=st.dpmax[i][0];
    }
    st.init(n);
    while(m--)
    {
        int l,r; readi(l,r);
        printf("%d\n",st.query(l,r));
    }
    return 0;
}