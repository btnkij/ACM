/**
* Number:uva11475
* Title:Extend to Palindrome
* Status:AC
* Tag:[hash]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
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

const int MAXN=100010;
const ull base=233;
ull xp[MAXN];
struct Hash
{
    ull h[MAXN];
    void init(char* s,int len)
    {
        h[0]=0;
        rep(i,1,len)h[i]=h[i-1]*base+s[i]-'a'+1;
    }
    inline ull substr(int l,int r)
    {
        return h[r]-h[l-1]*xp[r-l+1];
    }
}H,H1;
char s[MAXN],s1[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    xp[0]=1;
    repne(i,1,MAXN)xp[i]=xp[i-1]*base;
    while(reads(s+1)!=EOF)
    {
        int len=strlen(s+1);
        H.init(s,len);
        reverse_copy(s,s+len+1,s1+1);
        H1.init(s1,len);
        int ans=0;
        for(int i=len;i>=1;i--)
        {
            if(2*i-len>=1 && H.substr(i,len)==H1.substr(len-i+1,len-(2*i-len)+1))
                ans=max(ans,(len-i)*2+1);
            if(2*i-len-1>=1 && H.substr(i,len)==H1.substr(len-(i-1)+1,len-(2*i-len-1)+1))
                ans=max(ans,(len-i+1)*2);
        }
        ans=len-ans;
        reverse_copy(s,s+1+ans,s+len+1);
        puts(s+1);
    }
    return 0;
}