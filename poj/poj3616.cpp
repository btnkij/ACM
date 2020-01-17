/**
* Number:poj3616
* Title:Milking Time
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
    int beg,end,eff;
    bool operator<(const Node& rhs)const
    {
        return end<rhs.end;
    }
}nodes[1010];
int dp[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,r; readi(n,m,r);
    repne(i,0,m)readi(nodes[i].beg,nodes[i].end,nodes[i].eff);
    sort(nodes,nodes+m);
    int ans=0;
    for(int i=0;i<m;i++)
    {
        int tmp=0;
        for(int j=0;j<i;j++)
        {
            if(nodes[j].end+r<=nodes[i].beg)
                tmp=max(tmp,dp[j]);
        }
        dp[i]=nodes[i].eff+tmp;
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}