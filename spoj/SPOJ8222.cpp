/**
* Number:spoj8222
* Title:Substrings
* Status:AC
* Tag:[sam, 后缀自动机]
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

const int MAXN=255*2;
int dp[MAXN];
struct Node
{
    int len,fa,nxt[26];
}sam[MAXN];
int sz=1,last=1;
void append(int ch)
{
    int cur=++sz;
    int pre=last;
    sam[cur].len=sam[pre].len+1;
    dp[cur]=1;
    while(pre && !sam[pre].nxt[ch])
    {
        sam[pre].nxt[ch]=cur;
        pre=sam[pre].fa;
    }
    if(!pre)
    {
        sam[cur].fa=1;
    }
    else
    {
        int ori=sam[pre].nxt[ch];
        if(sam[ori].len==sam[pre].len+1)
        {
            sam[cur].fa=ori;
        }
        else
        {
            int clone=++sz;
            sam[clone]=sam[ori];
            sam[clone].len=sam[pre].len+1;
            sam[ori].fa=sam[cur].fa=clone;
            while(pre && sam[pre].nxt[ch]==ori)
            {
                sam[pre].nxt[ch]=clone;
                pre=sam[pre].fa;
            }
        }
    }
    last=cur;
}

char s[MAXN];
int bin[MAXN],id[MAXN];
int ans[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s+1);
    int len=strlen(s+1);
    rep(i,1,len)append(s[i]-'a');
    rep(i,1,sz)bin[sam[i].len]++;
    rep(i,1,len)bin[i]+=bin[i-1];
    rep(i,1,sz)id[bin[sam[i].len]--]=i;
    for(int i=sz;i>=1;i--)dp[sam[id[i]].fa]+=dp[id[i]];
    rep(i,1,sz)ans[sam[i].len]=max(ans[sam[i].len], dp[i]);
    for(int i=len;i>=1;i--)ans[i-1]=max(ans[i-1],ans[i]);
    rep(i,1,len)printf("%d\n",ans[i]);
    return 0;
}