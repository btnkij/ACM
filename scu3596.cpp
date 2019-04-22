/**
* Number:scu3596
* Title:Article Decryption 
* Status:AC
* Tag:[kmp, dp]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

char pat[1010][1010];
int nxt[1010];
void getnxt(char* pat, int len)
{
    nxt[0]=-1;
    int pre=-1, cur=0;
    while(cur<len)
    {
        if(pre==-1 || pat[pre]==pat[cur])
        {
            pre++, cur++;
            nxt[cur]=pat[pre]==pat[cur]?nxt[pre]:pre;
        }
        else pre=nxt[pre];
    }
}
const ll MOD = 835672545;
int match[1010][1010];
ll dp[1010];
char art[1010]; int L;
void kmp(int p, int len)
{
    char* pat=::pat[p];
    int i=0,j=0;
    while(i<L)
    {
        if(j==-1 || art[i]==pat[j])
        {
            i++, j++;
            if(j==len)
            {
                match[p][i]=len;
                j=nxt[len];
            }
        }
        else j=nxt[j];
    }
}
int len[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        repne(i,0,n)
        {
            reads(pat[i]);
        }
        reads(art);
        L=strlen(art);
        mset(match,0);
        repne(i,0,n)
        {
            len[i]=strlen(pat[i]);
            getnxt(pat[i], len[i]);
            kmp(i, len[i]);
        }
        mset(dp,0); dp[0]=1;
        for(int i=0;i<L;i++)
        for(int j=0;j<n;j++)
        {
            if(match[j][i+1])
            {
                dp[i+1]=(dp[i+1]+dp[i+1-len[j]])%MOD;
            }
        }
        printf("%lld\n", dp[L]);
    }
    return 0;
}