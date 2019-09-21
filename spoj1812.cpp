/**
* Number:
* Title:
* Status:?
* Tag:[]
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

const int MAXN=100000+10;
struct Node
{
    int pa,len,nxt[26];
}sam[MAXN<<1];
int sz=1,last=1;
void extend(int ch)
{
    int cur=++sz, pre=last;
    sam[cur].len=sam[pre].len+1;
    while(pre && !sam[pre].nxt[ch])
    {
        sam[pre].nxt[ch]=cur;
        pre=sam[pre].pa;
    }
    if(!pre)sam[cur].pa=1;
    else
    {
        int ori=sam[pre].nxt[ch];
        if(sam[ori].len==sam[pre].len+1)sam[cur].pa=ori;
        else
        {
            int clone=++sz;
            sam[clone]=sam[ori];
            sam[clone].len=sam[pre].len+1;
            sam[cur].pa=sam[ori].pa=clone;
            while(pre && sam[pre].nxt[ch]==ori)
            {
                sam[pre].nxt[ch]=clone;
                pre=sam[pre].pa;
            }
        }
    }
    last=cur;
}

char s[MAXN];
int dp[MAXN],dpall[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s);
    int len=strlen(s);
    repne(i,0,len)extend(s[i]-'a');
    clr(dpall,INF);
    while(reads(s)!=EOF)
    {
        len=strlen(s);
        clr(dp,0);
        int cur=1,tmp=0;
        repne(j,0,len)
        {
            int ch=s[j]-'a';
            if(sam[cur].nxt[ch])
            {
                cur=sam[cur].nxt[ch];
                tmp++;
                dp[cur]=max(dp[cur],tmp);
                continue;
            }
            while(cur && !sam[cur].nxt[ch])
                cur=sam[cur].pa;
            if(!cur)tmp=0,cur=1;
            else
            {
                tmp=sam[cur].len+1;
                cur=sam[cur].nxt[ch];
                dp[cur]=max(dp[cur],tmp);
            }
        }
        rep(i,2,sz)dpall[i]=min(dpall[i],dp[i]);
    }
    int ans=*max_element(dpall+2,dpall+sz+1);
    printf("%d\n",ans);
    return 0;
}