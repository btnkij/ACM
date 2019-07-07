/**
* Number:2178
* Title:苇名欧一郎
* Status:AC
* Tag:[状压dp]
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
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int S[1<<20];
int reward[20];
ll dp[1<<20];
char str[20];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    rep(kase,1,T)
    {
        int n; readi(n);
        for(int i=0;i<=n;i++)
        {
            reads(str);
            reward[i]=0;
            for(int j=0;j<n;j++)
                if(str[j]=='1')
                    reward[i]|=1<<j;
        }
        S[0]=reward[0];
        int all=(1<<n)-1;
        for(int sta=1;sta<=all;sta++)
        {
            int i=0;
            while(!(sta&(1<<i)))i++;
            S[sta]=S[sta^(1<<i)]|reward[i+1];
        }
        dp[0]=1;
        for(int sta=1;sta<=all;sta++)
        {
            dp[sta]=0;
            for(int i=0;(1<<i)<=sta;i++)
            {
                if((sta&(1<<i)) && (S[sta^(1<<i)]&(1<<i)))
                    dp[sta]+=dp[sta^(1<<i)];
            }
        }
        printf("Case %d: %lld\n",kase,dp[all]);
    }
    return 0;
}