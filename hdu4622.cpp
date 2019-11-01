/**
* Number:hdu4622
* Title:Reincarnation
* Status:AC
* Tag:[后缀自动机, sam]
* desc: 查询字符串任意区间中不同子串的个数
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

const int MAXN=2010; // 字符串长度
struct Node
{
    int pos;
    int link,len,nxt[26];
}sam[MAXN<<1];
int sz,last;
void init()
{
    sz=last=1;
    memset(&sam[1],0,sizeof(Node));
}
void extend(int ch, int pos)
{
    int cur=++sz, pre=last;
    memset(&sam[cur],0,sizeof(Node));
    sam[cur].len=sam[pre].len+1;
    sam[cur].pos=pos;
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

char s[MAXN];
int dp[MAXN][MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        clr(dp,0);
        reads(s+1);
        int len=strlen(s+1);
        rep(i,1,len)
        {
            init();
            auto& f=dp[i];
            rep(j,i,len)extend(s[j]-'a',j);
            rep(j,2,sz)f[sam[j].pos]+=sam[j].len-sam[sam[j].link].len;
            rep(j,i,len)f[j]+=f[j-1];
        }
        int q; readi(q);
        while(q--)
        {
            int l,r; readi(l,r);
            printf("%d\n",dp[l][r]);
        }
    }
    return 0;
}