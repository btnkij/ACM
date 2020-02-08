/**
* Number:spoj7258
* Title:Lexicographical Substring Search
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
    int link,len,nxt[26];
}sam[MAXN<<1];
int sz,last;
void init()
{
    sz=last=1;
    // memset(&sam[1],0,sizeof(Node));
}
void extend(int ch)
{
    int cur=++sz,pre=last;
    // memset(&sam[cur],0,sizeof(Node));
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
int rk[MAXN<<1];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s);
    int len=strlen(s);
    init();
    repne(i,0,len)extend(s[i]-'a');
    rep(i,1,sz)bin[sam[i].len]++;
    rep(i,1,len)bin[i]+=bin[i-1];
    rep(i,1,sz)ord[bin[sam[i].len]--]=i;
    for(int i=sz;i>=1;i--)
    {
        int u=ord[i];
        rk[u]=1;
        repne(j,0,26)rk[u]+=rk[sam[u].nxt[j]];
    }
    int q; readi(q);
    while(q--)
    {
        int u=1,k; readi(k);
        while(k)
        {
            repne(j,0,26)
            {
                int v=sam[u].nxt[j];
                if(rk[v]>=k)
                {
                    u=v, k--;
                    putchar('a'+j);
                    break;
                }
                else
                {
                    k-=rk[v];
                }
            }
        }
        puts("");
    }
    return 0;
}