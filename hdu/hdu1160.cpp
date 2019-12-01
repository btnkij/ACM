/**
* Number:hdu1160
* Title:FatMouse's Speed
* Status:AC
* Tag:[dp]
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
    int w,s,id;
    bool operator<(const Node& rhs)const
    {
        return w<rhs.w || w==rhs.w && s<rhs.s;
    }
}nodes[10010];
int dp[10010],pre[10010];
void show(int k)
{
    if(!k)return;
    show(pre[k]);
    printf("%d\n",nodes[k].id);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int w,s,n=0;
    while(readi(w,s)!=EOF)
    {
        int id=++n;
        nodes[id]=(Node){w,s,id};
    }
    sort(nodes+1,nodes+n+1);
    rep(i,1,n)
    {
        int t=0,k=0;
        repne(j,1,i)
        {
            if(nodes[j].w<nodes[i].w && nodes[j].s>nodes[i].s)
            {
                if(dp[j]>t)t=dp[j],k=j;
            }
        }
        dp[i]=t+1,pre[i]=k;
    }
    int* ans=max_element(dp+1,dp+n+1);
    printf("%d\n",*ans);
    show(ans-dp);
    return 0;
}