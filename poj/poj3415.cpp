/**
* Number:poj3415
* Title:Common Substrings
* Status:AC
* Tag:[后缀自动机, sam]
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

const int MAXN=1e5+10;
struct Node
{
    int link,len,nxt[52];
}sam[MAXN<<1];
int sz,last;
void init()
{
    sz=last=1;
    memset(&sam[1],0,sizeof(Node));
}
void extend(int ch)
{
    int cur=++sz,pre=last;
    memset(&sam[cur],0,sizeof(Node));
    sam[cur].len=sam[pre].len+1;
    while(pre && !sam[pre].nxt[ch])
    {
        sam[pre].nxt[ch]=cur;
        pre=sam[pre].link;
    }
    if(!pre)sam[cur].link=1;
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
int bin[MAXN],ord[MAXN<<1];
int rt[MAXN<<1],dp[MAXN<<1];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int k;
    while(readi(k)!=EOF && k)
    {
        reads(s);
        int len=strlen(s);
        init();
        clr(rt,0);
        repne(i,0,len)
        {
            s[i]=s[i]<='Z'?s[i]-'A':s[i]-'a'+26;
            extend(s[i]);
            rt[last]=1;
        }
        clr(bin,0);
        rep(i,2,sz)bin[sam[i].len]++;
        rep(i,1,len)bin[i]+=bin[i-1];
        rep(i,2,sz)ord[bin[sam[i].len]--]=i;
        for(int i=sz-1;i>=1;i--)
        {
            int u=ord[i];
            rt[sam[u].link]+=rt[u];
        }
        reads(s);
        len=strlen(s);
        repne(i,0,len)s[i]=s[i]<='Z'?s[i]-'A':s[i]-'a'+26;
        ll ans=0;
        int p=1,lcs=0;
        clr(dp,0);
        repne(i,0,len)
        {
            int ch=s[i];
            if(sam[p].nxt[ch])p=sam[p].nxt[ch],lcs++;
            else
            {
                while(p && !sam[p].nxt[ch])p=sam[p].link;
                if(!p)p=1,lcs=0;
                else lcs=sam[p].len+1,p=sam[p].nxt[ch];
            }
            if(lcs>=k)
            {
                int pre=sam[p].link;
                ans+=ll(lcs-max(k,sam[pre].len+1)+1)*rt[p];
                if(sam[pre].len>=k)dp[pre]++;
            }
        }
        for(int i=sz-1;i>=1;i--)
        {
            int u=ord[i],pre=sam[u].link;
            ans+=ll(sam[u].len-max(k,sam[pre].len+1)+1)*dp[u]*rt[u];
            if(sam[pre].len>=k)dp[pre]+=dp[u];
        }
        printf("%lld\n",ans);
    }
    return 0;
}