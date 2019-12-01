/**
* Number:ybt1543, loj10121
* Title:【例 3】与众不同
* Status:AC
* Tag:[rmq, 二分]
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

const int MAXN=2e5+10;
int len[MAXN],pre[MAXN],dummy[1000010],last[1000010];
bool comp(int lhs, int rhs)
{
    return len[lhs]<len[rhs];
}
struct sparse_table
{
    static const int LOGN = 18;
    int mm[MAXN];
    int dp[MAXN][LOGN];
    void init(int n)
    {
        for (int i = 2; i <= n; i++)
            mm[i] = i & (i - 1) ? mm[i - 1] : mm[i - 1] + 1;
        for(int i=0;i<n;i++)
        {
            dp[i][0]=i;
        }
        for (int k = 1; k < LOGN; k++)
        {
            int L = 1 << k;
            for (int i = 0; i + L - 1 < n; i++)
            {
                dp[i][k] = max(dp[i][k - 1], dp[i + (L >> 1)][k - 1], comp);
            }
        }
    }
    ll rmq(int lt, int rt)
    {
        int k = mm[rt - lt];
        return std::max(dp[lt][k], dp[rt - (1 << k) + 1][k], comp);
    }
}st;

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,0,n)
    {
        int t; readi(t);
        pre[i] = max(pre[i-1], last[t]);
        last[t]=i+1;
        len[i]=i-pre[i]+1;
    }
    st.init(n);
    while(m--)
    {
        int l,r; readi(l,r);
        int L=l, R=r;
        while(L<R)
        {
            int M=(L+R)>>1;
            if(pre[M]<l)L=M+1;
            else R=M;
        }
        int ans;
        if(pre[r]<=l)ans=r-l+1;
        else ans=max((R-1)-l+1,len[st.rmq(R,r)]);
        // int mid=st.rmq(l,r);
        // int ans=min(len[mid], mid-l+1);
        // if(mid<r)ans=max(ans, len[st.rmq(mid+1,r)]); // pre[mid+1]>=l ?
        printf("%d\n",ans);
    }
    return 0;
}