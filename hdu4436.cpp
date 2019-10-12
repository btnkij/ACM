/**
* Number:hdu4436
* Title:str2int
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

const int MAXN=2e5+10;
struct Node
{
    int link,len,nxt[11];
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
            sam[ori].link=sam[cur].link=clone;
            while(pre && sam[pre].nxt[ch]==ori)
            {
                sam[pre].nxt[ch]=clone;
                pre=sam[pre].link;
            }
        }
    }
    last=cur;
}

const int MOD=2012;
char s[MAXN];
int bin[MAXN],ord[MAXN<<1];
int sum[MAXN<<1],cnt[MAXN<<1];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        init();
        int len=0;
        repne(i,0,n)
        {
            reads(s);
            len+=strlen(s)+1;
            extend(10);
            for(char* p=s;*p;p++)extend(*p&0xF);
        }
        clr(bin,0);
        rep(i,1,sz)bin[sam[i].len]++;
        rep(i,1,len)bin[i]+=bin[i-1];
        rep(i,1,sz)ord[bin[sam[i].len]--]=i;
        clr(sum,0); clr(cnt,0);
        int ans=0;
        cnt[1]=1;
        rep(i,1,sz)
        {
            int u=ord[i];
            ans=(ans+sum[u])%MOD;
            rep(j,0,9)
            {
                int v=sam[u].nxt[j];
                if(!v)continue;
                if(j==0 && sam[u].len==0)continue;
                sum[v]=(sum[v]+sum[u]*10+cnt[u]*j)%MOD;
                cnt[v]=(cnt[v]+cnt[u])%MOD;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}