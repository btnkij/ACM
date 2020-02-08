/**
* Number:loj10179
* Title:「一本通 5.5 例 5」Banknotes
* Status:AC
* Tag:[dp, 多重背包, 单调队列]
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

int dp[20010],v[210],num[210];
struct Item 
{
    int val,idx;
}Q[20010];
int head,tail;
int main() {
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    clr(dp,INF);
    dp[0]=0;
    rep(i,1,n)readi(v[i]);
    rep(i,1,n)readi(num[i]);
    int m; readi(m);
    rep(i,1,n)
    {
        repne(r,0,v[i])
        {
            head=tail=0;
            for (int k = 0; k * v[i] + r <= m; k++) 
            {
                int x = k * v[i] + r;
                while (head!=tail && k - Q[head].idx > num[i]) head++;
                while (head!=tail && dp[x] - k <= Q[tail-1].val) tail--;
                Q[tail++]={ dp[x] - k, k };
                dp[x] = min(dp[x], Q[head].val + k);
            }
        }
    }
    printf("%d",dp[m]);
    return 0;
}