/**
* Number:uva690
* Title:Pipeline Scheduling
* Status:AC
* Tag:[dfs, 位运算]
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

int reserve[5];
char s[30];
int action[30],tot;
bool check(int* pre,int x)
{
    repne(i,0,5)if((pre[i]>>x)&reserve[i])return false;
    return true;
}
int ans;
void dfs(int* pre,int clk,int dep)
{
    if(dep>=10)
    {
        ans=min(ans,clk);
        return;
    }
    repne(i,0,tot)
    {
        int x=action[i];
        if(clk+x+(10-dep-1)*action[0]>=ans)return;
        if(check(pre,x))
        {
            int cur[5];
            repne(j,0,5)cur[j]=(pre[j]>>x)|reserve[j];
            dfs(cur,clk+x,dep+1);
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF && n)
    {
        repne(i,0,5)
        {
            reads(s);
            int mask=0;
            repne(j,0,n)mask|=(s[j]=='X')<<j;
            reserve[i]=mask;
        }
        tot=0;
        rep(i,1,n)if(check(reserve,i))action[tot++]=i;
        ans=n*10;
        dfs(reserve,n,1);
        printf("%d\n",ans);
    }
    return 0;
}