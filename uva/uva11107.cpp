/**
* Number:uva11107
* Title:Life Forms
* Status:AC
* Tag:[广义后缀自动机, exsam]
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

struct Node
{
    int len,fa,son[26];
}sam[200100];
int sz,last;
void extend(int ch)
{
    if(sam[last].son[ch])
    {
        int ori=sam[last].son[ch];
        if(sam[last].len+1==sam[ori].len)last=ori;
        else
        {
            int clone=++sz;
            sam[clone]=sam[ori];
            sam[clone].len=sam[last].len+1;
            sam[ori].fa=clone;
            for(int pre=last;pre && sam[pre].son[ch]==ori;pre=sam[pre].fa)
                sam[pre].son[ch]=clone;
            last=clone;
        }
        return;
    }
    int pre=last,cur=++sz;
    sam[cur].len=sam[pre].len+1;
    for(;pre && !sam[pre].son[ch];pre=sam[pre].fa)
        sam[pre].son[ch]=cur;
    if(!pre)sam[cur].fa=1;
    else
    {
        int ori=sam[pre].son[ch];
        if(sam[pre].len+1==sam[cur].len)sam[cur].fa=ori;
        else
        {
            int clone=++sz;
            sam[clone]=sam[ori];
            sam[clone].len=sam[pre].len+1;
            sam[cur].fa=sam[ori].fa=clone;
            for(;pre && sam[pre].son[ch]==ori;pre=sam[pre].fa)
                sam[pre].son[ch]=clone;
        }
    }
    last=cur;
}

char s[110][1010];
int vis[200100],cnt[200100];
int n,maxl;
char lcs[1010];
void dfs(int u,int dep)
{
    if(dep==maxl)
    {
        if(cnt[u]*2>n)
        {
            lcs[dep]='\0';
            puts(lcs);
        }
        return;
    }
    repne(i,0,26)
    {
        int v=sam[u].son[i];
        if(v && sam[u].len+1==sam[v].len)
        {
            lcs[dep]='a'+i;
            dfs(v,dep+1);
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(vis,-1);
    bool first=true;
    while(readi(n)!=EOF && n)
    {
        if(!first)puts("");
        first=false;
        memset(sam,0,sizeof(Node)*(sz+5));
        memset(vis,-1,sizeof(int)*(sz+5));
        memset(cnt,0,sizeof(int)*(sz+5));
        sz=1;
        repne(i,0,n)
        {
            reads(s[i]);
            last=1;
            for(char* p=s[i];*p;p++)extend(*p-'a');
        }
        repne(i,0,n)
        {
            int u=1;
            for(char* p=s[i];*p;p++)
            {
                u=sam[u].son[*p-'a'];
                for(int v=u; v && vis[v]!=i; v=sam[v].fa)
                {
                    vis[v]=i;
                    cnt[v]++;
                }
            }
        }
        maxl=0;
        rep(i,2,sz)if(cnt[i]*2>n)maxl=max(maxl,sam[i].len);
        if(maxl==0)puts("?");
        else dfs(1,0);
    }
    return 0;
}