/**
* Number:uva12206
* Title:Stammering Aliens
* Status:AC
* Tag:[hash, 二分]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <unordered_map>
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

const ull base=233;
ull xp[40010];
ull h[40010];
char s[40010];
inline ull substr(int l,int r)
{
    return h[r]-h[l-1]*xp[r-l+1];
}
unordered_map<ull,int> cnt;
int check(int n,int len,int mid)
{
    cnt.clear();
    int pos=-1;
    for(int i=1;i<=len-mid+1;i++)
    {
        ull t=substr(i,i+mid-1);
        cnt[t]++;
        if(cnt[t]>=n)pos=max(pos,i);
    }
    return pos;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    xp[0]=1;
    repne(i,1,40010)xp[i]=xp[i-1]*base;
    int n;
    while(readi(n)!=EOF && n)
    {
        reads(s+1);
        int len=strlen(s+1);
        rep(i,1,len)h[i]=h[i-1]*base+s[i]-'a'+1;
        int lt=0,rt=len-n+1;
        int ans=-1;
        while(lt<rt)
        {
            int mid=(lt+rt+1)>>1;
            int t=check(n,len,mid);
            if(t==-1)rt=mid-1;
            else lt=mid,ans=t;
        }
        if(ans==-1)puts("none");
        else printf("%d %d\n",lt,ans-1);
    }
    return 0;
}