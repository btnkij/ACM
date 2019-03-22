/**
* Number:ybt1541, loj10119
* Title:【例 1】数列区间最大值
* Status:AC
* Tag:[st表]
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

const int MAXN = 1e5+10;
const int MAXL = 16;
int dp[MAXN][MAXL+4], mm[MAXN];
void init(int n)
{
    repne(i,2,n)
        mm[i] = i&(i-1) ? mm[i-1] : mm[i-1]+1;
    for(int k=1; k<=MAXL; k++)
    {
        int len=1<<k;
        for(int rt=len; rt<=n; rt++)
        {
            int lt=rt-len+1;
            dp[lt][k]=max(dp[lt][k-1], dp[rt-(len>>1)+1][k-1]);
        }
    }
}
int query(int lt,int rt)
{
    int len=rt-lt+1;
    int k=mm[len-1];
    return max(dp[lt][k], dp[rt-(1<<k)+1][k]);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep(i,1,n)readi(dp[i][0]);
    init(n);
    while(m--)
    {
        int x,y; readi(x,y);
        printf("%d\n",query(x,y));
    }
    return 0;
}