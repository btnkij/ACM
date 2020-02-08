/**
* Number:p3804
* Title:【模板】后缀自动机
* Status:AC
* Tag:[后缀自动机, SAM]
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

const int MAXN=1e6+10;
struct Node
{
    int link,len,nxt[26];
}sam[MAXN<<1];
int sz=1,last=1;
void extend(int ch)
{
    int cur=++sz, pre=last;
    sam[cur].len=sam[pre].len+1;
    while(pre && !sam[pre].nxt[ch])
    {
        sam[pre].nxt[ch]=cur;
        pre=sam[pre].link;
    }
    if(pre==0)sam[cur].link=1;
    else
    {
        int ori=sam[pre].nxt[ch];
        if(sam[ori].len==sam[pre].len+1)sam[cur].link=ori;
        else
        {
            int clone=++sz;
            sam[clone]=sam[ori];
            sam[clone].len=sam[pre].len+1;
            sam[cur].link=sam[ori].link=clone;
            while(pre && sam[pre].nxt[ch]==ori)
            {
                sam[pre].nxt[ch]=clone;
                pre=sam[pre].link;
            }
        }
    }
    last=cur;
}

char s[MAXN];
int bin[MAXN],ord[MAXN<<1],dp[MAXN<<1];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s);
    int len=strlen(s);
    repne(i,0,len)
    {
        extend(s[i]-'a');
        dp[last]=1;
    }
    rep(i,2,sz)bin[sam[i].len]++;
    rep(i,1,len)bin[i]+=bin[i-1];
    rep(i,2,sz)ord[--bin[sam[i].len]]=i;
    ll ans=0;
    for(int i=sz-2;i>=0;i--)
    {
        int id=ord[i];
        if(dp[id]>1)ans=max(ans,(ll)dp[id]*sam[id].len);
        dp[sam[id].link]+=dp[id];
    }
    printf("%lld",ans);
    return 0;
}