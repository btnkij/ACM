/**
* Number:loj10149
* Title:「一本通 5.1 例 3」凸多边形的划分
* Status:AC
* Tag:[区间dp, int128]
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

typedef __int128 ll;
#define INF ((ll)(1e36));

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

ll read()
{
    ll num=0;
    char ch;
    do{ch=getchar();}while(!('0'<=ch && ch<='9'));
    do{num=(num<<3)+(num<<1)+(ch&0xF); ch=getchar();}while('0'<=ch && ch<='9');
    return num;
}
void print(ll num)
{
    if(num>=10)print(num/10);
    putchar(char(num%10)|0x30);
}

ll w[110];
ll dp[110][110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)w[i]=read();
    copy(w+1,w+n+1,w+n+1);
    for(int len=3;len<=n;len++)
    {
        for(int lt=1,rt=len; rt<=n<<1; lt++,rt++)
        {
            dp[lt][rt]=INF;
            for(int mid=lt+1; mid<rt; mid++)
            {
                dp[lt][rt]=min(
                    dp[lt][rt], 
                    dp[lt][mid]+dp[mid][rt]+w[lt]*w[mid]*w[rt]);
            }
        }
    }
    ll ans=INF;
    for(int i=1;i<=n;i++)
    {
        ans=min(ans, dp[i][i+n-1]);
    }
    print(ans);
    return 0;
}