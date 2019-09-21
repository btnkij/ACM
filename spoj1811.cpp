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

const int MAXN=1e2+10;
struct Node
{
    int pa,len,nxt[26];
}sam[MAXN<<1];
int sz=1,last=1;
void extend(int ch)
{
    int cur=++sz, pre=last;
    sam[cur].len=sam[pre].len+1;
    for(;pre && !sam[pre].nxt[ch];pre=sam[pre].pa)
        sam[pre].nxt[ch]=cur;
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
            for(;pre && sam[pre].nxt[ch]==ori;pre=sam[pre].pa)
                sam[pre].nxt[ch]=clone;
        }
    }
    last=cur;
}

char s1[MAXN],s2[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s1); reads(s2);
    int len1=strlen(s1),len2=strlen(s2);
    repne(i,0,len1)extend(s1[i]-'a');
    int ans=-INF,tmp=0;
    int i=1,j=0;
    while(j<len2)
    {
        int br=s2[j]-'a';
        if(i==0)
        {
            i=1,j++;
            tmp=0;
        }
        else if(sam[i].nxt[br])
        {
            i=sam[i].nxt[br];
            tmp++,j++;
        }
        else
        {
            i=sam[i].pa;
            tmp=sam[i].len;
        }
        ans=max(ans,tmp);
    }
    printf("%d\n",ans);
    return 0;
}