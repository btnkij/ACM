/**
* Number:ybt1540, loj133
* Title:打鼹鼠_二维树状数组
* Status:?
* Tag:[二维, 树状数组]
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
typedef long long ll;

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

struct binary_indexed_tree_2d
{
    ll data[5010][5010];
    int maxr, maxc; // 最大的下标
    void clear(int maxr, int maxc)
    {
        this->maxr = maxr, this->maxc = maxc;
        for(int i = 0; i <= maxr; i++)
        {
            memset(data[i], 0, sizeof(ll)*maxc);
        }
    }
    // 原数组 arr[r][c] += delta
    void add(int r, int c, ll delta)
    {
        for(int i = r; i <= maxr; i += i & -i)
        {
            for(int j = c; j <= maxc; j += j & -j)
            {
                data[i][j] += delta;
            }
        }
    }
    // 查询区间 [1, 1 : r, c] 的和
    ll query_sum(int r, int c)
    {
        ll sum = 0;
        for(int i = r; i; i ^= i & -i)
        {
            for(int j = c; j; j ^= j & -j)
            {
                sum += data[i][j];
            }
        }
        return sum;
    }
}T;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(T.maxr, T.maxc);
    int q;
    while(readi(q)!=EOF)
    {
        if(q==1)
        {
            int x,y,k; readi(x,y,k);
            T.add(x,y,k);
        }
        else if(q==2)
        {
            int a,b,c,d; readi(a,b,c,d);
            ll ans = T.query_sum(c,d) - T.query_sum(a-1,d)
             - T.query_sum(c,b-1) + T.query_sum(a-1,b-1);
            printf("%lld\n",ans);
        }
    }
    return 0;
}